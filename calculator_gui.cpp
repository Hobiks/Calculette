#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    double currentResult;
    QString pendingOperation;
};

Calculator::Calculator(QWidget *parent) : QWidget(parent), currentResult(0) {
    display = new QLineEdit(this);
    display->setReadOnly(true);

    QGridLayout *grid = new QGridLayout(this);

    QStringList buttons = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    int pos = 0;
    for (const QString &buttonText : buttons) {
        QPushButton *button = new QPushButton(buttonText, this);
        grid->addWidget(button, pos / 4, pos % 4);
        connect(button, &QPushButton::clicked, this, &Calculator::onButtonClicked);
        pos++;
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(display);
    layout->addLayout(grid);
    setLayout(layout);
    setWindowTitle("Calculator");
}

void Calculator::onButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString buttonText = button->text();

    if (buttonText == "C") {
        display->clear();
        currentResult = 0;
        pendingOperation.clear();
    } else if (buttonText == "=") {
        if (!pendingOperation.isEmpty()) {
            double operand = display->text().toDouble();
            if (pendingOperation == "+") currentResult += operand;
            else if (pendingOperation == "-") currentResult -= operand;
            else if (pendingOperation == "*") currentResult *= operand;
            else if (pendingOperation == "/") currentResult /= operand;
            display->setText(QString::number(currentResult));
            pendingOperation.clear();
        }
    } else {
        if (buttonText == "+" || buttonText == "-" || buttonText == "*" || buttonText == "/") {
            double operand = display->text().toDouble();
            if (pendingOperation.isEmpty()) currentResult = operand;
            else if (pendingOperation == "+") currentResult += operand;
            else if (pendingOperation == "-") currentResult -= operand;
            else if (pendingOperation == "*") currentResult *= operand;
            else if (pendingOperation == "/") currentResult /= operand;
            pendingOperation = buttonText;
            display->clear();
        } else {
            display->setText(display->text() + buttonText);
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calculator;
    calculator.resize(250, 200);
    calculator.show();
    return app.exec();
}