#include"MainWindow.h"
#include<QResizeEvent>
#include"eventfilterobject.h"
#include<QTimer>
#include <QFile>
MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
	initUi();
}

MainWindow::~MainWindow()
{
	delete m_settings;
}

void MainWindow::initUi()
{
	setFixedSize(350,640 );
	setWindowFlag(Qt::FramelessWindowHint);
	setWindowFlag(Qt::WindowType::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	installEventFilter(new eventFilterObject(this));

	RoleModel roleModel;
	for (int i = 0; i < 6; i++)
	{
		roleModel.addFrame(QString(":/assets/desktopRole/blackGril/action1-happy/%1.png").arg(i));
	}
	m_roleModels.insert("blackGirl/happy", roleModel);

	roleModel.clear();
	for (int i = 0; i < 6; i++)
	{
		roleModel.addFrame(QString(":/assets/desktopRole/blackGril/action2-sad/%1.png").arg(i));
	}
	m_roleModels.insert("blackGirl/sad", roleModel);

	roleModel.clear();
	for (int i = 0; i < 6; i++)
	{
		roleModel.addFrame(QString(":/assets/desktopRole/blackGril/action3-naughty/%1.png").arg(i));
	}
	m_roleModels.insert("blackGirl/naughty", roleModel);

	roleModel.clear();
	for (int i = 0; i < 6; i++)
	{
		roleModel.addFrame(QString(":/assets/desktopRole/blackGril/action4-shy/%1.png").arg(i));
	}
	m_roleModels.insert("blackGirl/shy", roleModel);

	roleModel.clear();
	for (int i = 0; i < 6; i++)
	{
		roleModel.addFrame(QString(":/assets/desktopRole/littleBoy/%1.png").arg(i));
	}
	m_roleModels.insert("littleBoy", roleModel);

	roleModel.clear();
	for (int i = 0; i < 6; i++)
	{
		roleModel.addFrame(QString(":/assets/desktopRole/summerGril/%1.png").arg(i));
	}
	m_roleModels.insert("summerGril", roleModel);


	m_roleModelLab = new QLabel(this);
	m_wallpaper = new WallpaperWidget;


	QTimer* timer = new QTimer(this);
	timer->callOnTimeout(this,&MainWindow::updateRoleModelAnimation);
	timer->start(500);

	m_currentRole = "summerGril";
	updateRoleModelAnimation();


	m_closeBtn = new QPushButton(this);
	m_settingBtn = new QPushButton(this); 
	m_closeBtn->move(129, 302);
	m_settingBtn->move(170, 302);
	m_closeBtn->setObjectName("closeBtn");
	m_settingBtn->setObjectName("settingsBtn");


	QFile file(":/assets/style.css");
	if (file.open(QIODevice::ReadOnly))
	{
		this->setStyleSheet(file.readAll());
	}

	m_settings = new Settings;


	connect(m_closeBtn, &QPushButton::released, this, &MainWindow::close);
	connect(m_settingBtn, &QPushButton::released, m_settings, &QWidget::show);
	connect(m_settings, &Settings::roleModelChanged, this, [=](const QString& r) {m_currentRole = r; });
	connect(m_settings, &Settings::wallpaperChanged, m_wallpaper, &WallpaperWidget::setWallpaper);
}

void MainWindow::updateRoleModelAnimation()
{
	m_frames = m_roleModels[m_currentRole].size();
	m_roleModelLab->setPixmap(m_roleModels[m_currentRole][m_index]);
	m_index = (m_index + 1) % m_frames;
}

void MainWindow::resizeEvent(QResizeEvent* ev)
{
	m_roleModelLab->resize(ev->size());
}

void MainWindow::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() == Qt::MouseButton::RightButton)
	{
		m_closeBtn->setVisible(!m_closeBtn->isVisible());
		m_settingBtn->setVisible(!m_settingBtn->isVisible());
	}
}
