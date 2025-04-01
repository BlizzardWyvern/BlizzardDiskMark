/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class CSettingsDlg : public QDialog
{
	Q_OBJECT

#ifdef SUISHO_SHIZUKU_SUPPORT
	static const int SIZE_X = 680;
	static const int SIZE_Y = 416;
#else
	static const int SIZE_X = 440;
	static const int SIZE_Y = 356;
#endif

public:
	CSettingsDlg(QWidget* parent = nullptr);
	virtual ~CSettingsDlg();

	void showEvent(QShowEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void closeEvent(QCloseEvent* event) override;

protected:
	// void DoDataExchange(); 
	bool OnInitDialog();

	int GetBlockSize(QString text);
	int GetType(QString text);

	QLabel* m_LabelType;
	QLabel* m_LabelSize;
	QLabel* m_LabelQueues;
	QLabel* m_LabelThreads;
	QLabel* m_LabelDefault;
	QLabel* m_LabelPeak;
	QLabel* m_LabelDemo;
	QLabel* m_LabelMeasureTime;
	QLabel* m_LabelIntervalTime;

	QComboBox* m_ComboBenchType0;
	QComboBox* m_ComboBenchType1;
	QComboBox* m_ComboBenchType2;
	QComboBox* m_ComboBenchType3;
	QComboBox* m_ComboBenchType4;
	QComboBox* m_ComboBenchType5;
	QComboBox* m_ComboBenchType8;
	QComboBox* m_ComboBenchSize0;
	QComboBox* m_ComboBenchSize1;
	QComboBox* m_ComboBenchSize2;
	QComboBox* m_ComboBenchSize3;
	QComboBox* m_ComboBenchSize4;
	QComboBox* m_ComboBenchSize5;
	QComboBox* m_ComboBenchSize8;
	QComboBox* m_ComboBenchQueues0;
	QComboBox* m_ComboBenchQueues1;
	QComboBox* m_ComboBenchQueues2;
	QComboBox* m_ComboBenchQueues3;
	QComboBox* m_ComboBenchQueues4;
	QComboBox* m_ComboBenchQueues5;
	QComboBox* m_ComboBenchQueues8;
	QComboBox* m_ComboBenchThreads0;
	QComboBox* m_ComboBenchThreads1;
	QComboBox* m_ComboBenchThreads2;
	QComboBox* m_ComboBenchThreads3;
	QComboBox* m_ComboBenchThreads4;
	QComboBox* m_ComboBenchThreads5;
	QComboBox* m_ComboBenchThreads8;

	QComboBox* m_ComboMeasureTime;
	QComboBox* m_ComboIntervalTime;

	QPushButton* m_ButtonSetDefault;
	QPushButton* m_ButtonSetNVMe8;
	QPushButton* m_ButtonOk;

private slots:
	void OnSetDefault();
	void OnSetNVMe8();
	void OnOk();
	void InitComboBox();

private:
	int m_BenchType[9];
	int m_BenchSize[9];
	int m_BenchQueues[9];
	int m_BenchThreads[9];

	int m_TestData;
	int m_MeasureTime;
	int m_IntervalTime;
	int m_Profile;
};
