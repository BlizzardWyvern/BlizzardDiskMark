/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once

#include "DiskMarkDlg.h"

#define ALL_0X00_0FILL "<0Fill>"

enum AFFINITY_MODE
{
	AFFINITY_DISABLED = 0,
	AFFINITY_ENABLED,
};

enum DISK_SPD_CMD
{
	TEST_CREATE_FILE = 0,
	TEST_DELETE_FILE,
	TEST_READ_0,
	TEST_READ_1,
	TEST_READ_2,
	TEST_READ_3,
	TEST_READ_4,
	TEST_READ_5,
	TEST_READ_6,
	TEST_READ_7,
	TEST_READ_8,
	TEST_WRITE_0,
	TEST_WRITE_1,
	TEST_WRITE_2,
	TEST_WRITE_3,
	TEST_WRITE_4,
	TEST_WRITE_5,
	TEST_WRITE_6,
	TEST_WRITE_7,
	TEST_WRITE_8,
	TEST_MIX_0,
	TEST_MIX_1,
	TEST_MIX_2,
	TEST_MIX_3,
	TEST_MIX_4,
	TEST_MIX_5,
	TEST_MIX_6,
	TEST_MIX_7,
	TEST_MIX_8,
};

quint64 ExecDiskBenchAll(void* dlg);
quint64 ExecDiskBenchAllPeak(void* dlg);
quint64 ExecDiskBenchAllReal(void* dlg);
quint64 ExecDiskBenchAllDemo(void* dlg);
quint64 ExecDiskBench0(void* dlg);
quint64 ExecDiskBench1(void* dlg);
quint64 ExecDiskBench2(void* dlg);
quint64 ExecDiskBench3(void* dlg);
quint64 ExecDiskBench4(void* dlg);
quint64 ExecDiskBench5(void* dlg);
quint64 ExecDiskBench6(void* dlg);
quint64 ExecDiskBench7(void* dlg);
