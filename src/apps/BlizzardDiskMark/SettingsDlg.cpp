/*  
 * Copyright (c) 2025  BlizzardWyvern, All rights reserved.
 *   
 * This file incorporates work covered by the following copyright and  
 * permission notice:  
 *  
 *     Copyright (c) 2007-2021 hiyohiyo
 * 
 *     Permission is hereby granted, free of charge, to any person obtaining
 * 	   a copy of this software and associated documentation files (the “Software”), 
 *     to deal in the Software without restriction, including without limitation 
 *     the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 *     and/or sell copies of the Software, and to permit persons to whom the 
 *     Software is furnished to do so, subject to the following conditions:
 * 
 * 	   The above copyright notice and this permission notice shall be included 
 *     in all copies or substantial portions of the Software.
 * 
 *     THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *     OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 *     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
 *     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 *     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 *     OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DiskMarkDlg.h"
#include "SettingsDlg.h"

CSettingsDlg::CSettingsDlg(QWidget* parent)
	: QDialog(parent),
	m_LabelType(new QLabel(this)),
	m_LabelSize(new QLabel(this)),
	m_LabelQueues(new QLabel(this)),
	m_LabelThreads(new QLabel(this)),
	m_LabelDefault(new QLabel(this)),
	m_LabelPeak(new QLabel(this)),
	m_LabelDemo(new QLabel(this)),
	m_LabelMeasureTime(new QLabel(this)),
	m_LabelIntervalTime(new QLabel(this)),
	m_ButtonSetDefault(new QPushButton(this)),
	m_ButtonSetNVMe8(new QPushButton(this)),
	m_ComboBenchType0(new QComboBox(this)),
	m_ComboBenchType1(new QComboBox(this)),
	m_ComboBenchType2(new QComboBox(this)),
	m_ComboBenchType3(new QComboBox(this)),
	m_ComboBenchType4(new QComboBox(this)),
	m_ComboBenchType5(new QComboBox(this)),
	m_ComboBenchType8(new QComboBox(this)),
	m_ComboBenchSize0(new QComboBox(this)),
	m_ComboBenchSize1(new QComboBox(this)),
	m_ComboBenchSize2(new QComboBox(this)),
	m_ComboBenchSize3(new QComboBox(this)),
	m_ComboBenchSize4(new QComboBox(this)),
	m_ComboBenchSize5(new QComboBox(this)),
	m_ComboBenchSize8(new QComboBox(this)),
	m_ComboBenchQueues0(new QComboBox(this)),
	m_ComboBenchQueues1(new QComboBox(this)),
	m_ComboBenchQueues2(new QComboBox(this)),
	m_ComboBenchQueues3(new QComboBox(this)),
	m_ComboBenchQueues4(new QComboBox(this)),
	m_ComboBenchQueues5(new QComboBox(this)),
	m_ComboBenchQueues8(new QComboBox(this)),
	m_ComboBenchThreads0(new QComboBox(this)),
	m_ComboBenchThreads1(new QComboBox(this)),
	m_ComboBenchThreads2(new QComboBox(this)),
	m_ComboBenchThreads3(new QComboBox(this)),
	m_ComboBenchThreads4(new QComboBox(this)),
	m_ComboBenchThreads5(new QComboBox(this)),
	m_ComboBenchThreads8(new QComboBox(this)),
	m_ComboMeasureTime(new QComboBox(this)),
	m_ComboIntervalTime(new QComboBox(this)),
	m_ButtonOk(new QPushButton(this))
{
	// CMainDialogFx* p = static_cast<CMainDialogFx*>(parent);

	// m_ZoomType = p->GetZoomType();
	// m_FontScale = p->GetFontScale();
	// m_FontRatio = p->GetFontRatio();
	// m_FontFace = p->GetFontFace();
	// m_FontRender = p->GetFontRender();
	// m_CurrentLangPath = p->GetCurrentLangPath();
	// m_DefaultLangPath = p->GetDefaultLangPath();
	// m_ThemeDir = p->GetThemeDir();
	// m_CurrentTheme = p->GetCurrentTheme();
	// m_DefaultTheme = p->GetDefaultTheme();
	// m_Ini = p->GetIniPath();

	// m_Profile = static_cast<CDiskMarkDlg*>(parent)->m_Profile;
	// m_MeasureTime = static_cast<CDiskMarkDlg*>(parent)->m_MeasureTime;
	// m_IntervalTime = static_cast<CDiskMarkDlg*>(parent)->m_IntervalTime;
	// m_TestData = static_cast<CDiskMarkDlg*>(parent)->m_TestData;
}

CSettingsDlg::~CSettingsDlg()
{
	delete m_LabelType;
	delete m_LabelSize;
	delete m_LabelQueues;
	delete m_LabelThreads;
	delete m_LabelDefault;
	delete m_LabelPeak;
	delete m_LabelDemo;
	delete m_LabelMeasureTime;
	delete m_LabelIntervalTime;
	delete m_ButtonSetDefault;
	delete m_ButtonSetNVMe8;
	delete m_ComboBenchType0;
	delete m_ComboBenchType1;
	delete m_ComboBenchType2;
	delete m_ComboBenchType3;
	delete m_ComboBenchType4;
	delete m_ComboBenchType5;
	delete m_ComboBenchType8;
	delete m_ComboBenchSize0;
	delete m_ComboBenchSize1;
	delete m_ComboBenchSize2;
	delete m_ComboBenchSize3;
	delete m_ComboBenchSize4;
	delete m_ComboBenchSize5;
	delete m_ComboBenchSize8;
	delete m_ComboBenchQueues0;
	delete m_ComboBenchQueues1;
	delete m_ComboBenchQueues2;
	delete m_ComboBenchQueues3;
	delete m_ComboBenchQueues4;
	delete m_ComboBenchQueues5;
	delete m_ComboBenchQueues8;
	delete m_ComboBenchThreads0;
	delete m_ComboBenchThreads1;
	delete m_ComboBenchThreads2;
	delete m_ComboBenchThreads3;
	delete m_ComboBenchThreads4;
	delete m_ComboBenchThreads5;
	delete m_ComboBenchThreads8;
	delete m_ComboMeasureTime;
	delete m_ComboIntervalTime;
	delete m_ButtonOk;
}

// void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialogFx::DoDataExchange(pDX);

// 	DDX_Control(pDX, IDC_LABEL_TYPE, m_LabelType);
// 	DDX_Control(pDX, IDC_LABEL_SIZE, m_LabelSize);
// 	DDX_Control(pDX, IDC_LABEL_QUEUES, m_LabelQueues);
// 	DDX_Control(pDX, IDC_LABEL_THREADS, m_LabelThreads);
// 	DDX_Control(pDX, IDC_LABEL_DEFAULT, m_LabelDefault);
// 	DDX_Control(pDX, IDC_LABEL_PEAK, m_LabelPeak);
// 	DDX_Control(pDX, IDC_LABEL_DEMO, m_LabelDemo);

// 	DDX_Control(pDX, IDC_LABEL_MEASURE_TIME, m_LabelMeasureTime);
// 	DDX_Control(pDX, IDC_LABEL_INTERVAL_TIME, m_LabelIntervalTime);
// //	DDX_Control(pDX, IDC_LABEL_AFFINITY, m_LabelAffinity);
// //	DDX_Control(pDX, IDC_LABEL_DATA, m_LabelData);

// 	DDX_Control(pDX, IDC_SET_DEFAULT, m_ButtonSetDefault);
// 	DDX_Control(pDX, IDC_SET_NVME_8, m_ButtonSetNVMe8);
// //	DDX_Control(pDX, IDC_SET_NVME_9, m_ButtonSetNVMe9);

// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_0, m_ComboBenchType0);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_1, m_ComboBenchType1);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_2, m_ComboBenchType2);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_3, m_ComboBenchType3);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_4, m_ComboBenchType4);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_5, m_ComboBenchType5);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_TYPE_8, m_ComboBenchType8);

// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_0, m_ComboBenchSize0);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_1, m_ComboBenchSize1);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_2, m_ComboBenchSize2);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_3, m_ComboBenchSize3);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_4, m_ComboBenchSize4);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_5, m_ComboBenchSize5);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_SIZE_8, m_ComboBenchSize8);

// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_0, m_ComboBenchQueues0);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_1, m_ComboBenchQueues1);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_2, m_ComboBenchQueues2);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_3, m_ComboBenchQueues3);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_4, m_ComboBenchQueues4);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_5, m_ComboBenchQueues5);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_QUEUE_8, m_ComboBenchQueues8);

// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_0, m_ComboBenchThreads0);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_1, m_ComboBenchThreads1);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_2, m_ComboBenchThreads2);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_3, m_ComboBenchThreads3);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_4, m_ComboBenchThreads4);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_5, m_ComboBenchThreads5);
// 	DDX_Control(pDX, IDC_COMBO_BENCH_THREAD_8, m_ComboBenchThreads8);

// //	DDX_Control(pDX, IDC_COMBO_DATA, m_ComboData);
// //	DDX_Control(pDX, IDC_COMBO_AFFINITY, m_ComboAffinity);
// 	DDX_Control(pDX, IDC_COMBO_MEASURE_TIME, m_ComboMeasureTime);
// 	DDX_Control(pDX, IDC_COMBO_INTERVAL_TIME, m_ComboIntervalTime);
// 	DDX_Control(pDX, IDC_OK, m_ButtonOk);
// }

// BEGIN_MESSAGE_MAP(CSettingsDlg, CDialogFx)
// 	ON_BN_CLICKED(IDC_SET_DEFAULT, &CSettingsDlg::OnSetDefault)
// 	ON_BN_CLICKED(IDC_SET_NVME_8, &CSettingsDlg::OnSetNVMe8)
// //	ON_BN_CLICKED(IDC_SET_NVME_9, &CSettingsDlg::OnSetNVMe9)
// 	ON_BN_CLICKED(IDC_OK, &CSettingsDlg::OnOk)
// END_MESSAGE_MAP()

void CSettingsDlg::OnSetDefault()
{
	int type[9] =    {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
	int size[9] =    { 1024, 1024,  4, 4, 1024,  4, 1024, 4, 1024 };
	int queues[9] =  {    8,    1, 32, 1,    8, 32,    1, 1,    8 };
	int threads[9] = {    1,    1,  1, 1,    1,  1,    1, 1,    1 };

	for (int i = 0; i < 9; i++)
	{
		m_BenchType[i] = type[i];
		m_BenchSize[i] = size[i];
		m_BenchQueues[i] = queues[i];
		m_BenchThreads[i] = threads[i];
	}

	m_TestData = 0;
	m_MeasureTime = 5;
	m_IntervalTime = 5;
	InitComboBox();
}

void CSettingsDlg::OnSetNVMe8()
{
	int type[9] =    {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
	int size[9] =    { 1024,  128,  4, 4, 1024,  4, 1024, 4, 1024 };
	int queues[9] =  {    8,   32, 32, 1,    8, 32,    1, 1,    8 };
	int threads[9] = {    1,    1, 16, 1,    1, 16,    1, 1,    1 };

	for (int i = 0; i < 9; i++)
	{
		m_BenchType[i] = type[i];
		m_BenchSize[i] = size[i];
		m_BenchQueues[i] = queues[i];
		m_BenchThreads[i] = threads[i];
	}

	m_TestData = 0;
	m_MeasureTime = 5;
	m_IntervalTime = 5;

	InitComboBox();
}

/*
void CSettingsDlg::OnSetNVMe9()
{
	int type[9] =    {   0,    0,  1, 1,    0,  1,    0, 1,    0 };
	int size[9] =    { 1024, 128,  4, 4, 1024,  4, 1024, 4, 1024 };
	int queues[9] =  {    8,  32, 32, 1,    8, 32,    1, 1,    8 };
	int threads[9] = {    4,   4, 16, 1,    4, 16,    1, 1,    1 };

	for (int i = 0; i < 9; i++)
	{
		m_BenchType[i] = type[i];
		m_BenchSize[i] = size[i];
		m_BenchQueues[i] = queues[i];
		m_BenchThreads[i] = threads[i];
	}

	m_TestData = 0;
	m_MeasureTime = 5;
	m_IntervalTime = 5;

	InitComboBox();
}
*/

void CSettingsDlg::showEvent(QShowEvent* event)
{
	// CDialogFx::OnInitDialog();

	QString cstr;

	int type[9] =    {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
	int size[9] =    { 1024, 1024,  4, 4, 1024,  4, 1024, 4, 1024 };
	int queues[9] =  {    8,    1, 32, 1,    8, 32,    1, 1,    8 };
	int threads[9] = {    1,    1,  1, 1,    1,  1,    1, 1,    1 };

	for (int i = 0; i < 9; i++)
	{
		cstr = QString("BenchType%1").arg(i);
		// m_BenchType[i] = settings.value(cstr, type[i]).toInt();
		if (m_BenchType[i] < 0 || m_BenchType[i] > 1) { m_BenchType[i] = type[i]; }

		cstr = QString("BenchSize%1").arg(i);
		// m_BenchSize[i] = settings.value(cstr, size[i]).toInt();
		if (m_BenchSize[i] <= 0 || m_BenchSize[i] > 8192) { m_BenchSize[i] = size[i]; }

		cstr = QString("BenchQueues%1").arg(i);
		// m_BenchQueues[i] = settings.value(cstr, queues[i]).toInt();
		if (m_BenchQueues[i] <= 0 || m_BenchQueues[i] > MAX_QUEUES) { m_BenchQueues[i] = queues[i]; }

		cstr = QString("BenchThreads%1").arg(i);
		// m_BenchThreads[i] = settings.value(cstr, threads[i]).toInt();
		if (m_BenchThreads[i] <= 0 || m_BenchThreads[i] > MAX_THREADS) { m_BenchThreads[i] = threads[i]; }
	}

	// m_TestData = GetPrivateProfileInt(L"Setting", L"TestData", 0, m_Ini);
	if (m_TestData < 0 || m_TestData > 1)
	{
		m_TestData = 0;
	}

	InitComboBox();

	m_LabelType->setText(tr("TYPE"));
	m_LabelSize->setText(tr("BLOCK_SIZE"));
	m_LabelQueues->setText(tr("QUEUES"));
	m_LabelThreads->setText(tr("THREADS"));
	m_LabelDefault->setText(" " + tr("PROFILE_DEFAULT"));
	m_LabelPeak->setText(" " + tr("PROFILE_PEAK_PERFORMANCE"));
	m_LabelDemo->setText(" " + tr("PROFILE_DEMO"));
	m_LabelMeasureTime->setText(" " + tr("MEASURE_TIME"));
	m_LabelIntervalTime->setText(" " + tr("INTERVAL_TIME"));

	m_ButtonSetDefault->setText(tr("DEFAULT"));
	setWindowTitle(tr("SETTINGS"));

	resizeEvent(nullptr);
}

void CSettingsDlg::InitComboBox()
{
	m_ComboBenchType0->clear();
	m_ComboBenchType1->clear();
	m_ComboBenchType2->clear();
	m_ComboBenchType3->clear();
	m_ComboBenchType4->clear();
	m_ComboBenchType5->clear();
	m_ComboBenchType8->clear();

	for (int i = 0; i < 2; i++)
	{
		QString cstr;
		if (i == 0)
		{
			cstr = "SEQ";
		}
		else
		{
			cstr = "RND";
		}
		m_ComboBenchType0->addItem(cstr); if (m_BenchType[0] == i) { m_ComboBenchType0->setCurrentIndex(i); }
		m_ComboBenchType1->addItem(cstr); if (m_BenchType[1] == i) { m_ComboBenchType1->setCurrentIndex(i); }
		m_ComboBenchType2->addItem(cstr); if (m_BenchType[2] == i) { m_ComboBenchType2->setCurrentIndex(i); }
		m_ComboBenchType3->addItem(cstr); if (m_BenchType[3] == i) { m_ComboBenchType3->setCurrentIndex(i); }
		m_ComboBenchType4->addItem(cstr); if (m_BenchType[4] == i) { m_ComboBenchType4->setCurrentIndex(i); }
		m_ComboBenchType5->addItem(cstr); if (m_BenchType[5] == i) { m_ComboBenchType5->setCurrentIndex(i); }
		m_ComboBenchType8->addItem(cstr); if (m_BenchType[8] == i) { m_ComboBenchType8->setCurrentIndex(i); }
	}

	m_ComboBenchSize0->clear();
	m_ComboBenchSize1->clear();
	m_ComboBenchSize2->clear();
	m_ComboBenchSize3->clear();
	m_ComboBenchSize4->clear();
	m_ComboBenchSize5->clear();
	m_ComboBenchSize8->clear();

	int blockSize[] = { 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 };
	for (int i = 0; i < 12; i++)
	{
		QString cstr;
		if (blockSize[i] >= 1024)
		{
			cstr = QString("%1MiB").arg(blockSize[i] / 1024);
		}
		else
		{
			cstr = QString("%1KiB").arg(blockSize[i]);
		}
		m_ComboBenchSize0->addItem(cstr); if (m_BenchSize[0] == blockSize[i]) { m_ComboBenchSize0->setCurrentIndex(i); }
		m_ComboBenchSize1->addItem(cstr); if (m_BenchSize[1] == blockSize[i]) { m_ComboBenchSize1->setCurrentIndex(i); }
		m_ComboBenchSize2->addItem(cstr); if (m_BenchSize[2] == blockSize[i]) { m_ComboBenchSize2->setCurrentIndex(i); }
		m_ComboBenchSize3->addItem(cstr); if (m_BenchSize[3] == blockSize[i]) { m_ComboBenchSize3->setCurrentIndex(i); }
		m_ComboBenchSize4->addItem(cstr); if (m_BenchSize[4] == blockSize[i]) { m_ComboBenchSize4->setCurrentIndex(i); }
		m_ComboBenchSize5->addItem(cstr); if (m_BenchSize[5] == blockSize[i]) { m_ComboBenchSize5->setCurrentIndex(i); }
		m_ComboBenchSize8->addItem(cstr); if (m_BenchSize[8] == blockSize[i]) { m_ComboBenchSize8->setCurrentIndex(i); }
	}

	// Queues
	m_ComboBenchQueues0->clear();
	m_ComboBenchQueues1->clear();
	m_ComboBenchQueues2->clear();
	m_ComboBenchQueues3->clear();
	m_ComboBenchQueues4->clear();
	m_ComboBenchQueues5->clear();
	m_ComboBenchQueues8->clear();

	int queues[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
	for (int i = 0; i < 10; i++)
	{
		QString cstr = QString::number(queues[i]);
		m_ComboBenchQueues0->addItem(cstr); if (m_BenchQueues[0] == queues[i]) { m_ComboBenchQueues0->setCurrentIndex(i); }
		m_ComboBenchQueues1->addItem(cstr); if (m_BenchQueues[1] == queues[i]) { m_ComboBenchQueues1->setCurrentIndex(i); }
		m_ComboBenchQueues2->addItem(cstr); if (m_BenchQueues[2] == queues[i]) { m_ComboBenchQueues2->setCurrentIndex(i); }
		m_ComboBenchQueues3->addItem(cstr); if (m_BenchQueues[3] == queues[i]) { m_ComboBenchQueues3->setCurrentIndex(i); }
		m_ComboBenchQueues4->addItem(cstr); if (m_BenchQueues[4] == queues[i]) { m_ComboBenchQueues4->setCurrentIndex(i); }
		m_ComboBenchQueues5->addItem(cstr); if (m_BenchQueues[5] == queues[i]) { m_ComboBenchQueues5->setCurrentIndex(i); }
		m_ComboBenchQueues8->addItem(cstr); if (m_BenchQueues[8] == queues[i]) { m_ComboBenchQueues8->setCurrentIndex(i); }
	}

	// Threads
	m_ComboBenchThreads0->clear();
	m_ComboBenchThreads1->clear();
	m_ComboBenchThreads2->clear();
	m_ComboBenchThreads3->clear();
	m_ComboBenchThreads4->clear();
	m_ComboBenchThreads5->clear();
	m_ComboBenchThreads8->clear();

	for (int i = 1; i <= 64; i++)
	{
		QString cstr = QString::number(i);
		m_ComboBenchThreads0->addItem(cstr); if (m_BenchThreads[0] == i) { m_ComboBenchThreads0->setCurrentIndex(i - 1); }
		m_ComboBenchThreads1->addItem(cstr); if (m_BenchThreads[1] == i) { m_ComboBenchThreads1->setCurrentIndex(i - 1); }
		m_ComboBenchThreads2->addItem(cstr); if (m_BenchThreads[2] == i) { m_ComboBenchThreads2->setCurrentIndex(i - 1); }
		m_ComboBenchThreads3->addItem(cstr); if (m_BenchThreads[3] == i) { m_ComboBenchThreads3->setCurrentIndex(i - 1); }
		m_ComboBenchThreads4->addItem(cstr); if (m_BenchThreads[4] == i) { m_ComboBenchThreads4->setCurrentIndex(i - 1); }
		m_ComboBenchThreads5->addItem(cstr); if (m_BenchThreads[5] == i) { m_ComboBenchThreads5->setCurrentIndex(i - 1); }
		m_ComboBenchThreads8->addItem(cstr); if (m_BenchThreads[8] == i) { m_ComboBenchThreads8->setCurrentIndex(i - 1); }
	}

	m_ComboMeasureTime->clear();
	int measureTimes[] = { 5, 10, 20, 30, 60 };
	for (int i = 0; i < 5; i++)
	{
		QString cstr = QString::number(measureTimes[i]);
		m_ComboMeasureTime->addItem(cstr); if (m_MeasureTime == measureTimes[i]) { m_ComboMeasureTime->setCurrentIndex(i); }
	}

	m_ComboIntervalTime->clear();
	int intervalTimes[] = { 0, 1, 3, 5, 10, 30, 60, 180, 300, 600 };
	for (int i = 0; i < 10; i++)
	{
		QString cstr = QString::number(intervalTimes[i]);
		m_ComboIntervalTime->addItem(cstr); if (m_IntervalTime == intervalTimes[i]) { m_ComboIntervalTime->setCurrentIndex(i); }
	}
}

int CSettingsDlg::GetType(QString text)
{
	if (text.contains("SEQ"))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int CSettingsDlg::GetBlockSize(QString text)
{
	QString numberOnly = text;
	numberOnly.remove(QRegularExpression("[^0-9]"));
	if(text.contains("M"))
	{
		return numberOnly.toInt() * 1024;
	}
	else
	{
		return numberOnly.toInt();
	}
}

void CSettingsDlg::OnOk()
{
	QString cstr;

	// m_ComboBenchType0->currentText(); WritePrivateProfileString(L"Setting", L"BenchType0", QString::number(GetType(m_ComboBenchType0->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchType1->currentText(); WritePrivateProfileString(L"Setting", L"BenchType1", QString::number(GetType(m_ComboBenchType1->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchType2->currentText(); WritePrivateProfileString(L"Setting", L"BenchType2", QString::number(GetType(m_ComboBenchType2->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchType3->currentText(); WritePrivateProfileString(L"Setting", L"BenchType3", QString::number(GetType(m_ComboBenchType3->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchType4->currentText(); WritePrivateProfileString(L"Setting", L"BenchType4", QString::number(GetType(m_ComboBenchType4->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchType5->currentText(); WritePrivateProfileString(L"Setting", L"BenchType5", QString::number(GetType(m_ComboBenchType5->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchType8->currentText(); WritePrivateProfileString(L"Setting", L"BenchType8", QString::number(GetType(m_ComboBenchType8->currentText())).toStdWString().c_str(), m_Ini);

	// m_ComboBenchSize0->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize0", QString::number(GetBlockSize(m_ComboBenchSize0->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchSize1->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize1", QString::number(GetBlockSize(m_ComboBenchSize1->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchSize2->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize2", QString::number(GetBlockSize(m_ComboBenchSize2->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchSize3->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize3", QString::number(GetBlockSize(m_ComboBenchSize3->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchSize4->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize4", QString::number(GetBlockSize(m_ComboBenchSize4->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchSize5->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize5", QString::number(GetBlockSize(m_ComboBenchSize5->currentText())).toStdWString().c_str(), m_Ini);
	// m_ComboBenchSize8->currentText(); WritePrivateProfileString(L"Setting", L"BenchSize8", QString::number(GetBlockSize(m_ComboBenchSize8->currentText())).toStdWString().c_str(), m_Ini);

	// m_ComboBenchQueues0->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues0", m_ComboBenchQueues0->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchQueues1->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues1", m_ComboBenchQueues1->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchQueues2->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues2", m_ComboBenchQueues2->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchQueues3->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues3", m_ComboBenchQueues3->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchQueues4->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues4", m_ComboBenchQueues4->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchQueues5->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues5", m_ComboBenchQueues5->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchQueues8->currentText(); WritePrivateProfileString(L"Setting", L"BenchQueues8", m_ComboBenchQueues8->currentText().toStdWString().c_str(), m_Ini);

	// m_ComboBenchThreads0->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads0", m_ComboBenchThreads0->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchThreads1->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads1", m_ComboBenchThreads1->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchThreads2->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads2", m_ComboBenchThreads2->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchThreads3->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads3", m_ComboBenchThreads3->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchThreads4->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads4", m_ComboBenchThreads4->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchThreads5->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads5", m_ComboBenchThreads5->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboBenchThreads8->currentText(); WritePrivateProfileString(L"Setting", L"BenchThreads8", m_ComboBenchThreads8->currentText().toStdWString().c_str(), m_Ini);

	// m_ComboMeasureTime->currentText(); WritePrivateProfileString(L"Setting", L"MeasureTime", m_ComboMeasureTime->currentText().toStdWString().c_str(), m_Ini);
	// m_ComboIntervalTime->currentText(); WritePrivateProfileString(L"Setting", L"IntervalTime", m_ComboIntervalTime->currentText().toStdWString().c_str(), m_Ini);

	// CDialogFx::OnCancel();
}

void CSettingsDlg::closeEvent(QCloseEvent* event)
{
	// CDialogFx::OnCancel();
}

void CSettingsDlg::resizeEvent(QResizeEvent* event)
{
	// CDialogFx::UpdateDialogSize();

	// ChangeZoomType(m_ZoomType);
	resize(SIZE_X, SIZE_Y);
	// UpdateBackground(FALSE, m_bDarkMode);
	QColor textColor = QColor(0, 0, 0);
	QColor textSelectedColor = QColor(0, 0, 0);

#ifdef SUISHO_SHIZUKU_SUPPORT
	int fontSize = 16;
	int comboHeight = 24;
#else
	int fontSize = 12;
	int comboHeight = 20;
#endif

// 	m_LabelType.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelSize.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelQueues.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelThreads.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelDefault.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelPeak.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelDemo.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelMeasureTime.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// 	m_LabelIntervalTime.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// //	m_LabelAffinity.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);
// //	m_LabelData.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, RGB(0, 0, 0), FW_NORMAL, m_FontRender);

// 	m_ComboBenchType0.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchType1.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchType2.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchType3.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchType4.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchType5.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchType8.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);

// 	m_ComboBenchSize0.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchSize1.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchSize2.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchSize3.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchSize4.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchSize5.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchSize8.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);

// 	m_ComboBenchQueues0.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchQueues1.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchQueues2.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchQueues3.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchQueues4.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchQueues5.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchQueues8.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);

// 	m_ComboBenchThreads0.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchThreads1.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchThreads2.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchThreads3.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchThreads4.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchThreads5.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboBenchThreads8.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);

// //	m_ComboData.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor,  FW_NORMAL, m_FontRender);
// //	m_ComboAffinity.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor,  FW_NORMAL, m_FontRender);
// 	m_ComboMeasureTime.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ComboIntervalTime.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, textColor, textSelectedColor, FW_NORMAL, m_FontRender);
// 	m_ButtonSetDefault.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, m_MeterText, FW_NORMAL, m_FontRender);
// 	m_ButtonSetNVMe8.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, m_MeterText, FW_NORMAL, m_FontRender);
// //	m_ButtonSetNVMe9.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, m_MeterText, FW_NORMAL, m_FontRender);
// 	m_ButtonOk.SetFontEx(m_FontFace, fontSize, fontSize, m_ZoomRatio, m_FontRatio, m_MeterText, FW_NORMAL, m_FontRender);

#ifdef SUISHO_SHIZUKU_SUPPORT
	m_LabelType.InitControl(8, 8, 160, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelSize.InitControl(176, 8, 160, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelQueues.InitControl(344, 8, 160, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelThreads.InitControl(512, 8, 160, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelDefault.InitControl(8, 32, 664, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelPeak.InitControl(8, 172, 664, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelDemo.InitControl(8, 256, 664, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
//	m_LabelData.InitControl(344, 316, 328, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
//	m_LabelAffinity.InitControl(8, 316, 328, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelMeasureTime.InitControl(8, 316, 328, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelIntervalTime.InitControl(344, 316, 328, 24, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);

	m_ComboBenchType0.InitControl(8,  60, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchType1.InitControl(8,  88, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchType2.InitControl(8, 116, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchType3.InitControl(8, 144, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchType4.InitControl(8, 200, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchType5.InitControl(8, 228, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchType8.InitControl(8, 284, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);

	m_ComboBenchSize0.InitControl(176,  60, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchSize1.InitControl(176,  88, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchSize2.InitControl(176, 116, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchSize3.InitControl(176, 144, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchSize4.InitControl(176, 200, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchSize5.InitControl(176, 228, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchSize8.InitControl(176, 284, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);

	m_ComboBenchQueues0.InitControl(344,  60, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchQueues1.InitControl(344,  88, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchQueues2.InitControl(344, 116, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchQueues3.InitControl(344, 144, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchQueues4.InitControl(344, 200, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchQueues5.InitControl(344, 228, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchQueues8.InitControl(344, 284, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);

	m_ComboBenchThreads0.InitControl(512,  60, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchThreads1.InitControl(512,  88, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchThreads2.InitControl(512, 116, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchThreads3.InitControl(512, 144, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchThreads4.InitControl(512, 200, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchThreads5.InitControl(512, 228, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboBenchThreads8.InitControl(512, 284, 160, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);

//	m_ComboData.InitControl(352, 344, 320, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
//	m_ComboAffinity.InitControl(16, 344, 320, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboMeasureTime.InitControl(8, 344, 328, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboIntervalTime.InitControl(344, 344, 328, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);

	m_ButtonSetDefault.InitControl(8, 376, 160, 32, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_ButtonSetNVMe8.InitControl(176, 376, 160, 32, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
//	m_ButtonSetNVMe9.InitControl(344, 376, 160, 32, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_ButtonOk.InitControl(512, 376, 160, 32, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
#else
	m_LabelType->setGeometry(8, 8, 100, 20);
	m_LabelSize->setGeometry(116, 8, 100, 20);
	m_LabelQueues->setGeometry(224, 8, 100, 20);
	m_LabelThreads->setGeometry(332, 8, 100, 20);
	m_LabelDefault->setGeometry(8, 28, 424, 20);
	m_LabelPeak->setGeometry(8, 148, 424, 20);
	m_LabelDemo->setGeometry(8, 220, 424, 20);
//	m_LabelAffinity->setGeometry(8, 272, 208, 20);
//	m_LabelData.InitControl(224, 272, 208, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_LEFT, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_LabelMeasureTime->setGeometry(8, 272, 208, 20);
	m_LabelIntervalTime->setGeometry(224, 272, 208, 20);

	m_ComboBenchType0->setGeometry(8, 52, 100, 20);
	m_ComboBenchType1->setGeometry(8, 76, 100, 20);
	m_ComboBenchType2->setGeometry(8, 100, 100, 20);
	m_ComboBenchType3->setGeometry(8, 124, 100, 20);
	m_ComboBenchType4->setGeometry(8, 172, 100, 20);
	m_ComboBenchType5->setGeometry(8, 196, 100, 20);
	m_ComboBenchType8->setGeometry(8, 244, 100, 20);

	m_ComboBenchSize0->setGeometry(116, 52, 100, 20);
	m_ComboBenchSize1->setGeometry(116, 76, 100, 20);
	m_ComboBenchSize2->setGeometry(116, 100, 100, 20);
	m_ComboBenchSize3->setGeometry(116, 124, 100, 20);
	m_ComboBenchSize4->setGeometry(116, 172, 100, 20);
	m_ComboBenchSize5->setGeometry(116, 196, 100, 20);
	m_ComboBenchSize8->setGeometry(116, 244, 100, 20);

	m_ComboBenchQueues0->setGeometry(224, 52, 100, 20);
	m_ComboBenchQueues1->setGeometry(224, 76, 100, 20);
	m_ComboBenchQueues2->setGeometry(224, 100, 100, 20);
	m_ComboBenchQueues3->setGeometry(224, 124, 100, 20);
	m_ComboBenchQueues4->setGeometry(224, 172, 100, 20);
	m_ComboBenchQueues5->setGeometry(224, 196, 100, 20);
	m_ComboBenchQueues8->setGeometry(224, 244, 100, 20);

	m_ComboBenchThreads0->setGeometry(332, 52, 100, 20);
	m_ComboBenchThreads1->setGeometry(332, 76, 100, 20);
	m_ComboBenchThreads2->setGeometry(332, 100, 100, 20);
	m_ComboBenchThreads3->setGeometry(332, 124, 100, 20);
	m_ComboBenchThreads4->setGeometry(332, 172, 100, 20);
	m_ComboBenchThreads5->setGeometry(332, 196, 100, 20);
	m_ComboBenchThreads8->setGeometry(332, 244, 100, 20);

//	m_ComboData.InitControl(232, 296, 200, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
//	m_ComboAffinity.InitControl(16, 296, 200, 200, m_ZoomRatio, &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawTransparent, m_bHighContrast, m_bDarkMode, RGB(255, 255, 255), RGB(160, 220, 255), RGB(255, 255, 255), 0);
	m_ComboMeasureTime->setGeometry(8, 296, 208, 20);
	m_ComboIntervalTime->setGeometry(224, 296, 208, 20);

	m_ButtonSetDefault->setGeometry(8, 324, 100, 24);
	m_ButtonSetNVMe8->setGeometry(116, 324, 100, 24);
//	m_ButtonSetNVMe9.InitControl(224, 324, 100, 24, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, SystemDraw, m_bHighContrast, m_bDarkMode, FALSE);
	m_ButtonOk->setGeometry(332, 324, 100, 24);
#endif

//	m_ButtonSetDefault.SetDrawFrame(TRUE);
//	m_ButtonSetNVMe8.SetDrawFrame(TRUE);
//	m_ButtonSetNVMe9.SetDrawFrame(TRUE);
//	m_ButtonOk.SetDrawFrame(TRUE);

	m_ButtonSetDefault->setCursor(Qt::PointingHandCursor);
	m_ButtonSetNVMe8->setCursor(Qt::PointingHandCursor);
//	m_ButtonSetNVMe9->setCursor(Qt::PointingHandCursor);
	m_ButtonOk->setCursor(Qt::PointingHandCursor);

	// SetDarkModeControl(m_ButtonOk.GetSafeHwnd(), m_bDarkMode);
	// SetDarkModeControl(m_ButtonSetDefault.GetSafeHwnd(), m_bDarkMode);
	// SetDarkModeControl(m_ButtonSetNVMe8.GetSafeHwnd(), m_bDarkMode);
	// // SetDarkModeControl(m_ButtonSetNVMe9.GetSafeHwnd(), m_bDarkMode);

	m_ComboBenchType0->setFixedHeight(comboHeight);
	m_ComboBenchType1->setFixedHeight(comboHeight);
	m_ComboBenchType2->setFixedHeight(comboHeight);
	m_ComboBenchType3->setFixedHeight(comboHeight);
	m_ComboBenchType4->setFixedHeight(comboHeight);
	m_ComboBenchType5->setFixedHeight(comboHeight);
	m_ComboBenchType8->setFixedHeight(comboHeight);

	m_ComboBenchSize0->setFixedHeight(comboHeight);
	m_ComboBenchSize1->setFixedHeight(comboHeight);
	m_ComboBenchSize2->setFixedHeight(comboHeight);
	m_ComboBenchSize3->setFixedHeight(comboHeight);
	m_ComboBenchSize4->setFixedHeight(comboHeight);
	m_ComboBenchSize5->setFixedHeight(comboHeight);
	m_ComboBenchSize8->setFixedHeight(comboHeight);

	m_ComboBenchQueues0->setFixedHeight(comboHeight);
	m_ComboBenchQueues1->setFixedHeight(comboHeight);
	m_ComboBenchQueues2->setFixedHeight(comboHeight);
	m_ComboBenchQueues3->setFixedHeight(comboHeight);
	m_ComboBenchQueues4->setFixedHeight(comboHeight);
	m_ComboBenchQueues5->setFixedHeight(comboHeight);
	m_ComboBenchQueues8->setFixedHeight(comboHeight);

	m_ComboBenchThreads0->setFixedHeight(comboHeight);
	m_ComboBenchThreads1->setFixedHeight(comboHeight);
	m_ComboBenchThreads2->setFixedHeight(comboHeight);
	m_ComboBenchThreads3->setFixedHeight(comboHeight);
	m_ComboBenchThreads4->setFixedHeight(comboHeight);
	m_ComboBenchThreads5->setFixedHeight(comboHeight);
	m_ComboBenchThreads8->setFixedHeight(comboHeight);

//	m_ComboData.SetItemHeightAll(comboHeight, m_ZoomRatio, m_FontRatio);
//	m_ComboAffinity.SetItemHeightAll(comboHeight, m_ZoomRatio, m_FontRatio);
	m_ComboMeasureTime->setFixedHeight(comboHeight);
	m_ComboIntervalTime->setFixedHeight(comboHeight);

// 	m_ComboBenchType0.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchType1.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchType2.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchType3.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchType4.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchType5.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchType8.SetMargin(0, 4, 0, 0, m_ZoomRatio);

// 	m_ComboBenchSize0.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchSize1.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchSize2.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchSize3.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchSize4.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchSize5.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchSize8.SetMargin(0, 4, 0, 0, m_ZoomRatio);

// 	m_ComboBenchQueues0.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchQueues1.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchQueues2.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchQueues3.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchQueues4.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchQueues5.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchQueues8.SetMargin(0, 4, 0, 0, m_ZoomRatio);

// 	m_ComboBenchThreads0.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchThreads1.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchThreads2.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchThreads3.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchThreads4.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchThreads5.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboBenchThreads8.SetMargin(0, 4, 0, 0, m_ZoomRatio);

// //	m_ComboData.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// //	m_ComboAffinity.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboMeasureTime.SetMargin(0, 4, 0, 0, m_ZoomRatio);
// 	m_ComboIntervalTime.SetMargin(0, 4, 0, 0, m_ZoomRatio);

	m_ComboBenchType4->setEnabled(false);
	m_ComboBenchType5->setEnabled(false);

	update();
}