#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/collection.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    mongocxx::instance inst{};
    mongocxx::client client(mongocxx::uri{});

    mongocxx::database db = client["mydata"];
    mongocxx::collection directorsCollection = db["test"];

    mongocxx::cursor cursor = directorsCollection.find({});

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    for (auto &&doc : cursor) {
        bsoncxx::document::element name = doc["name"];
        bsoncxx::document::element age = doc["age"];
        bsoncxx::document::element moviesElement = doc["movies"];

        QLabel *label = new QLabel(&window);
        label->setText(QString("Name: %1\nAge: %2").arg(name.get_utf8().value.to_string().c_str()).arg(age.get_int32().value));

        if (moviesElement && moviesElement.type() == bsoncxx::type::k_array) {
            QString moviesString = "Movies:\n";
            auto moviesArray = moviesElement.get_array().value;
            for (auto it = moviesArray.cbegin(); it != moviesArray.cend(); ++it) {
                if (it->type() == bsoncxx::type::k_utf8) {
                    moviesString += QString("  %1\n").arg(it->get_utf8().value.to_string().c_str());
                }
            }
            label->setText(label->text() + moviesString);
        }

        layout->addWidget(label);

        layout->addWidget(new QLabel("-------------------------------", &window));
    }

    window.show();

    return a.exec();
}
