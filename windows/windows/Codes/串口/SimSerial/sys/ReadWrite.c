#include <ntddk.h>
#include <ntddser.h>
#include "main.h"

extern DEVICE_ARRAY	gDeviceArray[ MAX_NUM_DEV ];
extern KSPIN_LOCK		gSpinLock;
extern KSPIN_LOCK		gPoolSpinLock;
extern LIST_ENTRY		gIdleQueue;

NTSTATUS
DispatchRead(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	)
{
	NTSTATUS			status;
	PDEVICE_EXTENSION	deviceExtension;
	KIRQL				OldIrql;
	BOOLEAN				bIsEmpty;

	status = STATUS_SUCCESS;
	DebugPrint(("Enter Read routine\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;


/*
	IrpStack = IoGetCurrentIrpStackLocation(Irp);
	ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	InputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	OutputLength= IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	DbgPrint("InputBufferLength:  %d     OutputBufferLength:   %d\n", InputLength, OutputLength );

	pOutBuf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;
	*/
	/*
	DebugPrint(("pOutBuf:   0x%x\n", pOutBuf ));
	*pOutBuf = 0x32;

	DebugPrint(("Exit read routine\n"));

  return CompleteRequest(Irp, status, info);
	*/
	// �����������У�һ����Irp���У�һ����Packet���С�
	// ��packet����Ϊ��ʱ����Irp�������
	// �����packet�������ȡ�����ݣ�����ReadIrp
	KeAcquireSpinLock( &deviceExtension->ReadQueueSpinLock, &OldIrql );
	bIsEmpty = IsListEmpty( &deviceExtension->ReadDataQueue );
	KeReleaseSpinLock( &deviceExtension->ReadQueueSpinLock, OldIrql );
	if( bIsEmpty ){
		IoMarkIrpPending( Irp );
		IoSetCancelRoutine( Irp, RequestCancelReadRoutine);
		ExInterlockedInsertTailList( &deviceExtension->ReadIrpQueue, &Irp->Tail.Overlay.ListEntry, &deviceExtension->CancelSpinLock );
		status = STATUS_PENDING;
		return status;
	}else{
		return CompleteReadIrp( deviceExtension, Irp );
	}
	
}
/*

*/
NTSTATUS
DispatchWrite(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	)
{
	PIO_STACK_LOCATION IrpStack;
	ULONG				ControlCode;
	ULONG				InputLength,OutputLength;
	NTSTATUS			status;
	PDEVICE_EXTENSION	deviceExtension;
	ULONG				info;
	PUCHAR				pInBuf;
	PLIST_ENTRY			link;
	ULONG				nTx;
	PPACKET				lpPacket;

	KIRQL				OldIrql;
	KIRQL				remoteOldIrql;
	PDEVICE_EXTENSION	remoteDev;
	PIRP				pendingMaskIrp;
	
	ULONG				i;
	PLIST_ENTRY			linkIrp;

	status = STATUS_SUCCESS;
	info = 0;
	DebugPrint(("---------      Enter Write routine    -------\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;

	IrpStack=IoGetCurrentIrpStackLocation(Irp);
	ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	InputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	OutputLength= IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	DbgPrint("InputBufferLength:  %d     OutputBufferLength:   %d\n", InputLength, OutputLength );

	pInBuf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;
	DebugPrint(("Data to write: \n"));
	for( i = 0; i < OutputLength; i++)
	{
		//*( pInBuf++ ) = i % 256;
		DbgPrint("%2x ", pInBuf[ i ] );
	}
	DbgPrint("\n");
	KeAcquireSpinLock( &gSpinLock, &OldIrql );
	if( deviceExtension->bIsConnected ){
		// �����ݴ����packet��
		// �����ն�����ReadIrp�ڶ�����
		// ���У���ɸ�ReadIrp
		// ���ޣ���ֱ�ӷ�����ն˵Ľ���packet������
		nTx = 0;
		remoteDev = gDeviceArray[ deviceExtension->remoteInstance ].deviceExtension;
		while( nTx < OutputLength ){
			if( link = ExInterlockedRemoveHeadList( &gIdleQueue, &gPoolSpinLock ) ){
				lpPacket = CONTAINING_RECORD( link, PACKET, ListEntry );
				DebugPrint(("lpPacket: %x\n", lpPacket ));
				lpPacket->nTotalNum = ( ( OutputLength - nTx ) > PACKET_SIZE  ) ? PACKET_SIZE : ( OutputLength - nTx );
				lpPacket->nReadBytes = 0;
				RtlCopyMemory( lpPacket->Buffer, &pInBuf[ nTx ], lpPacket->nTotalNum );
				ExInterlockedInsertTailList( &( remoteDev->ReadDataQueue ), link, &remoteDev->ReadQueueSpinLock );
				nTx += lpPacket->nTotalNum;

				// �쿴remoteInstance�Ƿ���ReadIrp
				linkIrp = ExInterlockedRemoveHeadList( &remoteDev->ReadIrpQueue, &remoteDev->CancelSpinLock );
				if( linkIrp ){
					// ��Զ���˿��Ѿ���ReadIrp��pending,����ɸ�ReadIrp
					pendingMaskIrp = CONTAINING_RECORD( linkIrp, IRP, Tail.Overlay.ListEntry );
					ASSERT( pendingMaskIrp );
					CompleteReadIrp( remoteDev, pendingMaskIrp );
				}
			}else{
				DebugPrint(("IdleQueue is empty!!!!\n"));
				break;
			}
		}
		info = nTx;
	}else{
		info = OutputLength;
	}
	KeReleaseSpinLock( &gSpinLock, OldIrql );
	DebugPrint(("Totally wrote %d\n---------      Exit Write routine    -------\n", info ));

	return CompleteRequest(Irp, status, info);
}

NTSTATUS
CompleteReadIrp(
	IN PDEVICE_EXTENSION	deviceExtension,
	IN PIRP					Irp
	)
{
	PIO_STACK_LOCATION	IrpStack;
	NTSTATUS			status;
	ULONG				ControlCode;
	ULONG				InputLength,OutputLength;
	PUCHAR				pOutBuf;
	ULONG				info;
	ULONG				nToReadBytes;
	PLIST_ENTRY			link;
	PPACKET				lpPacket;


	DebugPrint(("------  Enter CompleteReadIrp routine ( 0x%x )  --------\n", Irp));
	IrpStack = IoGetCurrentIrpStackLocation(Irp);

	DebugPrint(("GetCurrentIrpStackLocation OK\n"));
	ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	InputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	OutputLength= IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	DbgPrint("InputBufferLength:  %d     OutputBufferLength:   %d\n", InputLength, OutputLength );

	pOutBuf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;

	link = ExInterlockedRemoveHeadList( &deviceExtension->ReadDataQueue, &deviceExtension->ReadQueueSpinLock );
	ASSERT( link );
	lpPacket = CONTAINING_RECORD( link, PACKET, ListEntry );
	DebugPrint(("lpPacket: %x!\n", lpPacket ));
	nToReadBytes = ( lpPacket->nTotalNum - lpPacket->nReadBytes );
	ASSERT( nToReadBytes > 0);
	nToReadBytes = ( nToReadBytes > OutputLength ) ? OutputLength : nToReadBytes;
	RtlCopyMemory( pOutBuf, &( lpPacket->Buffer[ lpPacket->nReadBytes ] ), nToReadBytes );
	lpPacket->nReadBytes += nToReadBytes;
	if( lpPacket->nReadBytes == lpPacket->nTotalNum ){
		RtlZeroMemory( lpPacket, sizeof( PACKET ) );
		DebugPrint(("ZeroMemory lpPacket!\n"));
		ExInterlockedInsertTailList( &gIdleQueue, &( lpPacket->ListEntry ), &gPoolSpinLock );
	}else{
		ExInterlockedInsertHeadList( &deviceExtension->ReadDataQueue, link, &deviceExtension->ReadQueueSpinLock );
	}
	status = STATUS_SUCCESS;
	DebugPrint(("--------      Exit ReadIrp routine   -----------\n"));
	return CompleteRequest( Irp, status, nToReadBytes );
}