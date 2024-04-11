#include <ntifs.h>

VOID PcreateProcessNotifyRoutine(IN HANDLE ParentId, IN HANDLE ProcessId, IN BOOLEAN Create)
{
	if (Create)
	{
		DbgPrint("[Create]ProcessId:%d     ParentId:%d\n", HandleToLong(ProcessId), HandleToLong(ParentId));
	}
	else
	{
		DbgPrint("[Close]ProcessId:%d     ParentId:%d\n", HandleToLong(ProcessId), HandleToLong(ParentId));
	}
}

VOID MyDriverUnLoad(PDRIVER_OBJECT driver_object)
{
	DbgPrint("[Driver]driver_object::%p\n", driver_object);
	DbgPrint("[Log]DriverUnLoad!!!\n");
	PsSetCreateProcessNotifyRoutine(PcreateProcessNotifyRoutine, TRUE);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING path)
{
	DbgPrint("[Driver]driver_object::%p\n", driver_object);
	DbgPrint("[Driver]path::%wZ\n", path);


	driver_object->DriverUnload = MyDriverUnLoad;
	NTSTATUS status = PsSetCreateProcessNotifyRoutine(PcreateProcessNotifyRoutine, FALSE);
	return status;
}