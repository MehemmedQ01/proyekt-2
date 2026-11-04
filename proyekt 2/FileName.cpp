#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Gradiyent {
    string ad;
    double kqqiymeti;
    int sayi;

public:
    Gradiyent(string ad, double kqqiymeti, int sayi) {
        this->ad = ad;
        this->kqqiymeti = kqqiymeti;
        this->sayi = sayi;
    }

    string AdGradiyent() {
        return ad;
    }
    double KqqiymetiGradiyent() {
        return kqqiymeti;
    }
    int SayiGradiyent() {
        return sayi;
    }
    void SayArtir(int miqdar) {
        sayi += miqdar;
    }
    void SayAzalt(int miqdar) {
        sayi -= miqdar;
    }
};
class Food {
    string ad;
    double qiymeti;
    int sayi;
    vector<string>gradiyent;
public:
    Food(string ad, double qiymeti, int sayi, vector<string>gradiyent) {
        this->ad = ad;
        this->qiymeti = qiymeti;
        this->sayi = sayi;
        this->gradiyent = gradiyent;
    }
    string GetFood() {
        return ad;
    }
    vector<string>Getgradiyent() {
        return gradiyent;
    }
    double GetQiymet() {
        return qiymeti;
    }
    int GetSayi() {
        return sayi;
    }
    void SayAzalt(int miqdar) {
        sayi -= miqdar;
    }
};
class Restoran {
private:
    vector<Gradiyent> anbar;
    vector<Food> menyu;
    double balans = 0;
public:
    double GetBalans() {
        return balans;
    }
    vector<Food> GetMenyu() {
        return menyu;
    }
    void elaveGradiyent(Gradiyent gradiyent) {
        for (int i = 0; i < anbar.size(); i++) {
            if (anbar[i].AdGradiyent() == gradiyent.AdGradiyent()) {
                anbar[i].SayArtir(gradiyent.SayiGradiyent());
                cout << "Ingredientin sayi artirildi!\n";
                return;
            }
        }

        anbar.push_back(gradiyent);
        cout << "Yeni ingredient elave edildi!\n";
    }
    bool movcuddur(string gradiyentAdi) {
        for (int i = 0; i < anbar.size(); i++) {
            if (anbar[i].AdGradiyent() == gradiyentAdi and anbar[i].SayiGradiyent() > 0) {
                return true;
            }
        }
        return false;
    }
    int IngredientSayi(string ad) {
        for (auto& g : anbar) {
            if (g.AdGradiyent() == ad) {
                return g.SayiGradiyent();
            }
        }
        return 0;
    }
    void elaveFood(Food yemek) {
        vector<string> gradiyentler = yemek.Getgradiyent();
        for (int i = 0; i < gradiyentler.size(); i++) {
            if (!movcuddur(gradiyentler[i])) {
                cout << "Qradiyent yoxdur!\n";
                return;
            }
        }
        menyu.push_back(yemek);
    }

    void silGradiyent(string gradiyentAdi) {
        for (int i = 0; i < anbar.size(); i++) {
            if (anbar[i].AdGradiyent() == gradiyentAdi) {
                anbar.erase(anbar.begin() + i);

                for (int j = 0; j < menyu.size();) {
                    bool tapildi = false;

                    for (string ad : menyu[j].Getgradiyent()) {
                        if (ad == gradiyentAdi) {
                            tapildi = true;
                            break;
                        }
                    }

                    if (tapildi) {
                        menyu.erase(menyu.begin() + j);
                    }
                    else {
                        j++;
                    }

                }
                cout << "Qradiyent ve ona aid yemekler silindi!\n";
                return;
            }
        }
        cout << "Qradiyent tapilmadi!\n";
    }

    void silFood(string yemekAdi) {
        for (int i = 0; i < menyu.size(); i++) {
            if (menyu[i].GetFood() == yemekAdi) {
                menyu.erase(menyu.begin() + i);
                cout << "Yemek ugurla silindi!\n";
                return;
            }
        }
        cout << "Yemek tapilmadi!\n";
    }

    bool SifarisTesdiq(vector<pair<string, int>> sebet, double& userBalans) {
        if (sebet.empty()) {
            cout << "Sebet bosdur!\n";
            return false;
        }

        vector<pair<string, int>> serfiyyat;
        double mebleg = 0;

        for (auto s : sebet) {
            bool tapildi = false;

            for (auto& f : menyu) {
                if (f.GetFood() == s.first) {
                    tapildi = true;

                    if (s.second <= 0 || f.GetSayi() < s.second) {
                        cout << "Yemek miqdari kifayet deyil!\n";
                        return false;
                    }

                    mebleg += f.GetQiymet() * s.second;

                    for (string ad : f.Getgradiyent()) {
                        bool var = false;

                        for (auto& x : serfiyyat) {
                            if (x.first == ad) {
                                x.second += s.second;
                                var = true;
                                break;
                            }
                        }

                        if (!var) {
                            serfiyyat.push_back({ ad, s.second });
                        }
                    }

                    break;
                }
            }

            if (!tapildi) {
                cout << "Yemek menyuda yoxdur!\n";
                return false;
            }
        }

        if (userBalans < mebleg) {
            cout << "Balansinizda kifayet qeder pul yoxdur!\n";
            cout << "Sifaris meblegi: " << mebleg << " AZN\n";
            cout << "User balansiniz: " << userBalans << " AZN\n";
            return false;
        }

        for (auto s : serfiyyat) {
            if (IngredientSayi(s.first) < s.second) {
                cout << s.first << " ingredienti kifayet deyil!\n";
                return false;
            }
        }

        for (auto s : serfiyyat) {
            for (auto& g : anbar) {
                if (g.AdGradiyent() == s.first) {
                    g.SayAzalt(s.second);
                    break;
                }
            }
        }

        for (auto s : sebet) {
            for (auto& f : menyu) {
                if (f.GetFood() == s.first) {
                    f.SayAzalt(s.second);
                    break;
                }
            }
        }

        userBalans -= mebleg;

        balans += mebleg;

        for (int i = 0; i < (int)menyu.size();) {
            if (menyu[i].GetSayi() <= 0) {
                menyu.erase(menyu.begin() + i);
            }
            else {
                i++;
            }
        }

        cout << "\nSifaris tesdiqlendi!\n";
        cout << "Umumi mebleg: " << mebleg << " AZN\n";
        cout << "User-in yeni balansı: " << userBalans << " AZN\n";
        cout << "Restoran balansı: " << balans << " AZN\n";

        return true;
    }
};
class Menyu {
public:
    void Goster(Restoran restoran) {
        vector<Food> yemekler = restoran.GetMenyu();

        if (yemekler.empty()) {
            cout << "Menyuda yemek yoxdur!\n";
            return;
        }

        for (int i = 0; i < yemekler.size(); i++) {
            cout << yemekler[i].GetFood() << " - " << yemekler[i].GetQiymet() << " AZN\n";
        }
    }
};
class User {
protected:
    string ad;
    string username;
    string password;
    double balans;
public:
    User(string ad, string username, string password, double balans = 0) {
        this->ad = ad;
        this->username = username;
        this->password = password;
        this->balans = balans;
    }

    string GetUsername() {
        return username;
    }

    double GetBalans() {
        return balans;
    }

    void BalansArtir(double mebleg) {
        if (mebleg > 0) {
            balans += mebleg;
            cout << "Balans artirildi!\n";
        }
        else {
            cout << "Mebleg musbet olmalidir!\n";
        }
    }
    double& BalansRef() {
        return balans;
    }

    bool Login(string username, string password) {
        return this->username == username && this->password == password;
    }
};

class Admin : public User {
public:
    Admin(string ad, string username, string password) : User(ad, username, password) {

    }

    void Panel(Restoran& restoran) {
        int secim;

        do {
            cout << "\n--- ADMIN PANEL ---\n";
            cout << "1. Menyuya yemek elave et\n";
            cout << "2. Yemek sil\n";
            cout << "3. Menyuya bax\n";
            cout << "4. Anbara ingredient elave et\n";
            cout << "5. Cixis\n";
            cout << "Secim: ";
            cin >> secim;

            if (secim == 1) {
                string ad;
                double qiymet;
                int sayi, say;
                vector<string> gradiyentler;

                cout << "Yemeyin adi: ";
                cin >> ad;
                cout << "Yemeyin qiymeti: ";
                cin >> qiymet;
                cout << "Yemeyin sayi: ";
                cin >> sayi;
                cout << "Nece nov ingredient var? ";
                cin >> say;

                if (say <= 0) {
                    cout << "Yemeyin en az bir ingredienti olmalidir!\n";
                    continue;
                }

                for (int i = 0; i < say; i++) {
                    string ingredientAdi;

                    cout << i + 1 << ". Ingredientin adi: ";
                    cin >> ingredientAdi;

                    gradiyentler.push_back(ingredientAdi);
                }

                Food yemek(ad, qiymet, sayi, gradiyentler);
                restoran.elaveFood(yemek);
            }

            else if (secim == 2) {
                string yemekAdi;

                cout << "Silinecek yemeyin adi: ";
                cin >> yemekAdi;

                restoran.silFood(yemekAdi);
            }

            else if (secim == 3) {
                Menyu menyu;
                menyu.Goster(restoran);
            }

            else if (secim == 4) {
                string ad;
                double qiymet;
                int sayi;

                cout << "Ingredientin adi: ";
                cin >> ad;
                cout << "1 kq qiymeti (AZN): ";
                cin >> qiymet;
                cout << "Miqdar (kq): ";
                cin >> sayi;

                if (qiymet <= 0 || sayi <= 0) {
                    cout << "Qiymet ve miqdar musbet olmalidir!\n";
                    continue;
                }
                restoran.elaveGradiyent(Gradiyent(ad, qiymet, sayi));
            }
            else if (secim == 5) {
                cout << "Admin panelinden cixildi.\n";
            }
            else {
                cout << "Yanlis secim!\n";
            }

        } while (secim != 5);
    }
};

void UserPanel(Restoran& restoran, User& user) {
    vector<pair<string, int>> sebet;
    int secim;

    do {
        cout << "\n--- USER PANEL ---\n";
        cout << "1. Menyuya bax\n";
        cout << "2. Sebete yemek elave et\n";
        cout << "3. Sebete bax\n";
        cout << "4. Sifarisi tesdiq et\n";
        cout << "5. Balansa pul elave et\n";
        cout << "6. Balansa bax\n";
        cout << "0. Geri qayit\n";
        cout << "Secim: ";
        cin >> secim;

        if (secim == 1) {
            Menyu m;
            m.Goster(restoran);
        }

        else if (secim == 2) {
            string ad;
            int say;
            bool tapildi = false;

            Menyu m;
            m.Goster(restoran);

            cout << "Yemeyin adi: ";
            cin >> ad;
            cout << "Miqdar: ";
            cin >> say;

            if (say <= 0) {
                cout << "Miqdar musbet olmalidir!\n";
                continue;
            }

            for (auto f : restoran.GetMenyu()) {
                if (f.GetFood() == ad) {
                    tapildi = true;

                    int sebetdekiSay = 0;

                    for (auto s : sebet) {
                        if (s.first == ad) {
                            sebetdekiSay = s.second;
                            break;
                        }
                    }

                    if (sebetdekiSay + say > f.GetSayi()) {
                        cout << "Bu qeder yemek yoxdur!\n";
                        break;
                    }

                    bool var = false;

                    for (auto& s : sebet) {
                        if (s.first == ad) {
                            s.second += say;
                            var = true;
                            break;
                        }
                    }

                    if (!var) {
                        sebet.push_back({ ad, say });
                    }

                    cout << "Sebete elave edildi!\n";
                    break;
                }
            }

            if (!tapildi) {
                cout << "Yemek tapilmadi!\n";
            }
        }

        else if (secim == 3) {
            if (sebet.empty()) {
                cout << "Sebet bosdur!\n";
            }
            else {
                cout << "\n--- SEBET ---\n";

                for (auto s : sebet) {
                    cout << s.first << " - Miqdar: "
                        << s.second << "\n";
                }
            }
        }

        else if (secim == 4) {
            if (restoran.SifarisTesdiq(sebet, user.BalansRef())) {
                sebet.clear();
            }
        }

        else if (secim == 5) {
            double mebleg;

            cout << "Elave edilecek mebleg (AZN): ";
            cin >> mebleg;

            user.BalansArtir(mebleg);
        }

        else if (secim == 6) {
            cout << "Cari balansiniz: "
                << user.GetBalans() << " AZN\n";
        }

        else if (secim != 0) {
            cout << "Yanlis secim!\n";
        }

    } while (secim != 0);
}
int main() {
    Admin admin("Administrator", "admin", "1234");
    User user("Istifadeci", "user", "1234");
    Restoran restoran;

    int secim;

    do {
        cout << "\n===== RESTORAN SISTEMI =====\n";
        cout << "1. Admin Login\n";
        cout << "2. User\n";
        cout << "0. Cixis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            string username, password;

            cout << "Admin username: ";
            cin >> username;
            cout << "Admin password: ";
            cin >> password;

            if (admin.Login(username, password)) {
                cout << "Admin girisi ugurludur!\n";
                admin.Panel(restoran);
            }
            else {
                cout << "Username ve ya password yanlisdir!\n";
            }
        }
        else if (secim == 2) {
            UserPanel(restoran, user);
        }
        else if (secim != 0) {
            cout << "Yanlis secim!\n";
        }

    } while (secim != 0);

    return 0;
}