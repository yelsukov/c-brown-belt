#include <string>

using namespace std;

class INotifier {
public:
    virtual void Notify(const string &message) = 0;
};

class SmsNotifier : public INotifier {
public:
    explicit SmsNotifier(const string new_phone) : phone(new_phone) {};

    void Notify(const string &message) override {
        SendSms(this->phone, message);
    };

protected:
    string phone;
};

class EmailNotifier : public INotifier {
public:
    explicit EmailNotifier(const string new_email) : email(new_email) {};

    void Notify(const string &message) override {
        SendEmail(this->email, message);
    };

protected:
    string email;
};
