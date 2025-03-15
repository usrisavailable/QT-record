#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QValidator>
#include <QDoubleValidator>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr) 
    : QMainWindow(parent){
        m_edit = new QTextEdit();
        setCentralWidget(m_edit);

        auto menuBar = new QMenuBar;
        setMenuBar(menuBar);

        QMenu* menu = menuBar->addMenu("File");
        QAction* action = menu->addAction("open");
        action->setObjectName("open");
        menu->addAction("save")->setObjectName("save");

        QSettings settings("settings.ini", QSettings::IniFormat);
        bool enableAutoWrap = settings.value("autoWrap", true).toBool(); 

        menu = menuBar->addMenu("Edit");
        action = menu->addAction("autoWrap"); 
        action->setCheckable(true);
        action->setChecked(enableAutoWrap);
        action->setObjectName("autoWrap");

        QMetaObject::connectSlotsByName(this);
    }

protected:
    void closeEvent(QCloseEvent *event) override{
        QMessageBox::StandardButton ret = QMessageBox::question(this, "confirm", "are you sure to close?");
        if (ret == QMessageBox::Yes){
            event->accept();
        }else{
            event->ignore();
        }
        QMainWindow::closeEvent(event);
    }


private Q_SLOTS:
    void on_open_triggered(){
        QString fileName = QFileDialog::getOpenFileName(this, "open file");
        if (fileName.isEmpty()){
            return;
        }
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)){
            QMessageBox::warning(this, "error", "open file failed");
            return;
        }
        QByteArray data = file.readAll();
        QString text = QString::fromUtf8(data);
        m_edit->setPlainText(text);
    }

    void on_save_triggered(){
        QFile file(m_fileName);
        if(!file.open(QFile::WriteOnly)){
            QMessageBox::warning(this, "error", "save file failed");
            return;
        }

        QString text = m_edit->toPlainText();
        QByteArray data = text.toUtf8();
        file.write(data);
    }
    //信号的参数类型必须和槽的参数类型一致，而且个数也要一致（可以多，不能少）
    void on_autoWrap_triggered(bool checked){
        qDebug() << "autoWrap" << checked;
        //枚举对象在QTextEdit中,设置按照宽度自动换行
        m_edit->setLineWrapMode(checked ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
        QSettings settings("settings.ini", QSettings::IniFormat);
        settings.setValue("autoWrap", checked);
    }
private:
    QTextEdit* m_edit;
    QString m_fileName;
};

#include "main.moc"

int main(int argc, char **argv){
    setlocale(LC_ALL, "zh_CN.UTF-8");

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
