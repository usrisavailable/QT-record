#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>

//QObject类是所有QT对象的基类，QObject类提供了对象树的支持
//QT维护了一颗对象树
//对象树的作用：当父对象被释放时，子对象也会被释放
//对象树的好处：不需要手动释放对象，不需要担心内存泄漏
//对象树的注意事项：当对象树中的对象被释放时，会自动释放子对象，但是子对象的指针并不会被置为nullptr
//因此手动释放子对象会导致内存泄漏（C++11中，delete一个nullptr是没有任何effect的）

//QObject的派生关系
//QObejct->QWidget->QMainWindow, QLabel, QPushButton, QComboBox等

//QT中的main函数
int main(int argc, char **argv){
    //单例模式实现类对象，每个Qt程序只能有一个QApplication对象
    QApplication app(argc, argv);

    {
        QObject obj1;
        QObject *obj2 = new QObject();
        obj2->setParent(&obj1); //obj2的父对象是obj1
    }//这里obj1和obj2都会被释放


    //只能有一个主窗口
    QMainWindow window; //这里面就是一个事件循环
    window.setWindowTitle("QT学习");
    window.setGeometry(500, 500, 200, 200);

    QLabel *label = new QLabel;//显示创建一个对象，没有指定父对象,这个对象不会被释放
    label->setText("Hello World");
    //设置对齐方式,参数是个枚举值，可以组合使用
    label->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    //层叠样式表，对应前端的CSS，qt中叫做qss
    //C++14中的原始字符串，R"()"，里面的内容不会被转义
    label->setStyleSheet(R"(
        QLabel{
        color: #333333; 
        font-size: 40px; 
        background-color: #66ccff
    })");
    window.setCentralWidget(label); //label作为窗口的中心控件，共用了同一个父对象widget
    window.show();

    return app.exec();
}
