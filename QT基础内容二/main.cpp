#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

//QObejct->QWidget->QMainWindow, QLabel, QPushButton, QComboBox等

//就把基类看作是特殊的成员，后面初始化派生类自己的成员
//调用默认构造函数时不指定参数，那就默认是个nullptr
class Label : public QLabel{
public:
    explicit Label(QWidget *parent = nullptr) : QLabel(parent){
        setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    
        setStyleSheet(R"(
        QLabel{
        color: #333333; 
        font-size: 20px; 
        margin: 5px;
        background-color: #66ccff
        })");
    }
};

class MainWindow : public QMainWindow{
public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent){
        setWindowTitle("九九乘法表");
        setGeometry(500, 500, 200, 200);

        //窗口的中心窗口，这个窗口是个QWidget，可以放置其他的QWidget，只有这一个窗口
        QWidget *centralWidget = new QWidget;
        setCentralWidget(centralWidget);

        //设置中心窗口的布局方式，这是个派生类，基类是QLayout，是个纯抽象类
        //当然还有其他的布局方式，比如QHBoxLayout，QGridLayout等
        QGridLayout *layout = new QGridLayout();
        centralWidget->setLayout(layout);

        //QT提供的QString类，可以直接用+号连接字符串
        for(int i = 1 ; i <= 9; i++)
        for(int j = 1; j <= 9; j++){
            Label *label = new Label;
            //label->setText("Hello" + QString::number(i));
            label->setText(QString("%1 = %2").arg(QString::number(i) + "*" + QString::number(j)).arg(i * j));
            layout->addWidget(label, i, j);
        }

    }
};

int main(int argc, char **argv){
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
