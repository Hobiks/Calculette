#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    QString currentOperation;
    double firstNumber;
};

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    display = new QLineEdit;
    mainLayout->addWidget(display);

    QGridLayout *gridLayout = new QGridLayout;

    // Create buttons for digits
    for (int i = 0; i < 10; ++i) {
        QPushButton *button = new QPushButton(QString::number(i));
        connect(button, &QPushButton::clicked, this, &Calculator::onButtonClicked);
        gridLayout->addWidget(button, i / 3, i % 3);
    }

    // Create buttons for operations
    QStringList operations = { "+", "-", "*", "/", "=" };
    for (const QString &operation : operations) {
        QPushButton *button = new QPushButton(operation);
        connect(button, &QPushButton::clicked, this, &Calculator::onButtonClicked);
        gridLayout->addWidget(button, 3, operations.indexOf(operation));
    }

    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);

    setWindowTitle("Calculator");
}

void Calculator::onButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();
        if (buttonText == "=") {
            double secondNumber = display->text().toDouble();
            double result = 0;

            if (currentOperation == "+") {
                result = firstNumber + secondNumber;
            } else if (currentOperation == "-") {
                result = firstNumber - secondNumber;
            } else if (currentOperation == "*") {
                result = firstNumber * secondNumber;
            } else if (currentOperation == "/") {
                if (secondNumber != 0) {
                    result = firstNumber / secondNumber;
                } else {
                    display->setText("Error");
                    return;
                }
            }
            display->setText(QString::number(result));
            currentOperation.clear();
        } else {
            if (buttonText == "+" || buttonText == "-" || buttonText == "*" || buttonText == "/") {
                firstNumber = display->text().toDouble();
                currentOperation = buttonText;
                display->clear();
            } else {
                display->setText(display->text() + buttonText);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calculator;
    calculator.resize(400, 300);
    calculator.show();
    
    return app.exec();
}

#include "main.moc"