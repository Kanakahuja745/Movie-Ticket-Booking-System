#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Movie{
    
    private:
    int movieID;
    string movieName;
    int totalSeats;
    bool *seats;
    
    public:
    Movie(int id, string name, int total){
        movieID=id;
        movieName=name;
        totalSeats=total;
        seats=new bool[totalSeats];
        for(int i=0;i<totalSeats;i++){
            seats[i]=false;
        }
    }
    
    void displayMovie(){
        cout<<"Movie ID:"<<movieID<<endl;
        cout<<"Movie name:"<<movieName<<endl;
        cout<<"Total seats available:"<<totalSeats<<endl;
    }
    
    void showAvailableSeats(){
        cout<<"Available seats:"<<endl;
        for(int i=0;i<totalSeats;i++){
            if(seats[i]==false){
                cout<<i+1<<" ";
                
            }
        }
        cout<<endl;
    }
    
    bool bookSeat(int seatNo){
    
        if(seatNo<1||seatNo>totalSeats){
            return false;
        }
        if(seats[seatNo-1]){
            seats[seatNo-1]==false;
            return true;
        }
        return false;
    }
    
    void cancelSeat(){
        int seatNo;
        seats[seatNo-1]=false;
    }
    
    int getID(){
        return movieID;
    }
    
    ~Movie(){
        delete[] seats;
    }
    
    };
    
    class Booking{
        private:
        string customerName;
        string phone;
        int movieID;
        int seatCount;
        int *bookedSeats;
        
        public:
        Booking(string customer,string phon,int movie,int count){
            customerName=customer;
            phone=phon;
            movieID=movie;
            seatCount=count;
            bookedSeats= new int[seatCount];
        }
        
        Booking(const Booking &b){
            customerName=b.customerName;
            phone=b.phone;
            movieID=b.movieID;
            seatCount=b.seatCount;
            
            bookedSeats=new int[seatCount];
            for(int i=0;i<seatCount;i++){
                bookedSeats[i]=b.bookedSeats[i];
            }
        }
        
        void setSeat( int index, int seatNo){
           bookedSeats[index]=seatNo;
        }
        
        void generateReceipt(){
            ofstream file("bookings.txt",ios::app);
            file<<"   TICKET RECEIPT   "<<endl;
            file<<"Name:"<<customerName<<endl;
            file<<"Phone Number:"<<phone<<endl;
            file<<"Movie ID:"<<movieID<<endl;
            file<<"Seats:";
            for(int i=0;i<seatCount;i++){
                file<<bookedSeats[i]<<" ";
            }
            file.close();
            cout<<"\nReceipt generated successfully!\n";
        }
        
        ~Booking(){
            delete[] bookedSeats;
        }
         };
         
bool adminLogin(){
    string username;
    string password;
    cout<<"\nAdmin username:";
    cin>>username;
    cout<<"Enter password:";
    cin>>password;
    
    if (username == "admin" && password == "1234") {
        cout << "\nLogin Successful!\n";
        return true;
    }
    cout << "\nInvalid Credentials!\n";
    return false;
    }
    


int main(){
    Movie* movies = new Movie[2]{
        Movie(1, "Inception", 10),
        Movie(2, "Avengers", 10)
    };

    int choice;

    while (true) {
        cout << "\n   MOVIE BOOKING SYSTEM   ";
        cout << "\n1. View Movies";
        cout << "\n2. Book Ticket";
        cout << "\n3. Admin Panel";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < 2; i++)
                movies[i].displayMovie();
        }

        else if (choice == 2) {
            string name, phone;
            int id, seats;

            cout << "\nEnter Name: ";
            cin >> name;
            cout << "Enter Phone: ";
            cin >> phone;

            cout << "Enter Movie ID: ";
            cin >> id;

            cout << "How many seats? ";
            cin >> seats;

            Booking b(name, phone, id, seats);

            for (int i = 0; i < 2; i++) {
                if (movies[i].getID() == id) {

                    movies[i].showAvailableSeats();

                    for (int j = 0; j < seats; j++) {
                        int seatNo;
                        cout << "Enter seat number: ";
                        cin >> seatNo;

                        if (movies[i].bookSeat(seatNo))
                            b.setSeat(j, seatNo);
                        else
                            cout << "Seat already booked!\n";
                    }

                    cout << "\nProcessing Payment...\n";
                    cout << "Payment Successful!\n";

                    b.generateReceipt();
                }
            }
        }

        else if (choice == 3) {
            if (adminLogin()) {
                cout << "\nAdmin Access Granted.\n";
                for (int i = 0; i < 2; i++)
                    movies[i].displayMovie();
            }
        }

        else if (choice == 4) {
            delete[] movies;
            cout << "\nThank You!\n";
            break;
        }
    }

    return 0;

}