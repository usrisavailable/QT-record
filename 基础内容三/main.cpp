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


class MainWindow : public QMainWindow{
private:
    QLineEdit *m_lineEdit;
    //枚举类型拥有全局的命名空间，可以直接使用，当然仅限public
    enum Operator{
        None,
        Plus,
        Minus,
        Multiply,
        Divide,
    };
    double m_lastValue;
    Operator m_lastOperator = None;
public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent){
        setWindowTitle("九九乘法表");
        setGeometry(400, 400, 200, 200);

        setCentralWidget(new QWidget);
        QGridLayout *layout = new QGridLayout();
        //QT中的get函数不需要使用get，set函数需要使用set
        centralWidget()->setLayout(layout);

        m_lineEdit = new QLineEdit;
        m_lineEdit->setText("0");
        m_lineEdit->setValidator(new QDoubleValidator); //设置验证器，只能输入数字
        layout->addWidget(m_lineEdit);

        QList<QPair<Operator, QString>> operators = {
            {Plus, "+"},
            {Minus, "-"},
            {Multiply, "*"},
            {Divide, "/"},
        };


        //结构化绑定，直接将pair中的两个值绑定到op和name中
        for(auto const &[op, name] : operators) {
            QPushButton *button = new QPushButton;
            button->setText(name);
            layout->addWidget(button);
            //connect函数的第一个参数是发送信号的对象，第二个参数是信号，第三个参数是接收信号的对象，第四个参数是槽函数
            //第四个参数可以是一个函数，也可以是一个lambda表达式
            //无论是哪一个对象被销毁，connect函数都会自动断开连接
            //这样就避免了使用野指针导致内存泄漏的问题
            //这里使用了lambda表达式，[this, op]表示捕获this指针和op变量
            //如果按引用捕获的话，在回调函数可能会导致悬空引用的问题，所以最好明确指定捕获方式
            connect(button, &QPushButton::clicked, this, [this, op](){
                this->pressOperator(op);
            });
        }

        QPushButton *equalButton = new QPushButton;
        equalButton->setText("=");
        layout->addWidget(equalButton);
        connect(equalButton, &QPushButton::clicked, this, &MainWindow::pressEqual);

        QPushButton *zeroButton = new QPushButton;
        zeroButton->setText("C");
        //layout->addWidget(zeroButton, 1, 0);
        layout->addWidget(zeroButton);
        connect(equalButton, &QPushButton::clicked, this, [this]{
            this->m_lineEdit->setText("0");
            m_lastOperator = None;
        });

    }

    void setLineEditText(QString text){
        int pos;
        if (m_lineEdit->validator()->validate(text, pos) != QValidator::Invalid){
            m_lineEdit->setText(text);
        }
    }

    void pressOperator(Operator op){
        double value = m_lineEdit->text().toDouble();
        m_lastValue = value;
        m_lastOperator = op;
        m_lineEdit->setText("0");
    }

    void pressEqual(){
        double value1 = m_lastValue;
        double value2 = m_lineEdit->text().toDouble();  
        double value;
        switch(m_lastOperator){
            case Plus:
                value = value1 + value2;
                break;
            case Minus:
                value = value1 - value2;
                break;
            case Multiply:
                value = value1 * value2;
                break;
            case Divide:
                value = value1 / value2;
                break;
            case None:
                value = value2;
                break;
        }
        m_lineEdit->setText(QString::number(value));
    }
};

int main(int argc, char **argv){
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
