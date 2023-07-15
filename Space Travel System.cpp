#include<bits/stdc++.h>
using namespace std;

int cons=10000000; // to set price of ticket

struct Date{
    int d,m,y;
};

//to get number of days between dates

const int Days_of_months[12]
    = { 31, 28, 31, 30, 31, 30, 
       31, 31, 30, 31, 30, 31 };
  
// This function counts number of leap years before the given date
int countLeapYears(Date d)
{
    int years = d.y;

  
    // Check if the current year needs to be considered for the count of leap years or not
    if (d.m <= 2)
        years--;
  
    // An year is a leap year if it is a multiple of 4, multiple of 400 and not a multiple of 100.
    return years / 4 
           - years / 100
           + years / 400;
}
  
// This function returns number of days between two given dates
int getDifference(Date dt1, Date dt2)
{
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1'
  
    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;
  
    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += Days_of_months[i];
  
    // Since every leap year is of 366 days, Add a day for every leap year
    n1 += countLeapYears(dt1);
  
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2'
  
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += Days_of_months[i];
    n2 += countLeapYears(dt2);
  
    // return difference between two counts
    return (n2 - n1);
}

//here function to get number of days bettween two dates ends

struct Planet_Coordinates{
    float x,y,z;
};

class Planet{
    public:
        string name;
        struct Planet_Coordinates location;
    
        void set_name(string name_in){
            name=name_in;
        }

        string get_name(){
            return name;
        }

        void set_coordinates(int x,int y,int z){
            location.x=x;
            location.y=y;
            location.z=z;
        }

        struct Planet_Coordinates get_coordinates(){
            return location;
        }
};

// here are 3 different types of planets 

class Hot:public Planet{
    public:
        string atmosphere;
        string water;

        string get_atmosphere_info(){
            return atmosphere;
        }

        string get_water_info(){
            return water;
        }
};

class Cold:public Planet{
    public:
        string atmosphere;
        string water;

        string get_atmosphere_info(){
            return atmosphere;
        }

        string get_water_info(){
            return water;
        }
};

class Red:public Planet{
    public:
        string inhabitant;
        string water;

        string get_inhabitant_info(){
            return inhabitant;
        }

        string get_water_info(){
            return water;
        }
};


//function to get distance between two planets

float distance(Planet s, Planet d){
    float dist = sqrt(pow(d.location.x - s.location.x, 2) + pow(d.location.y - s.location.y, 2) + pow(d.location.z - s.location.z, 2) * 1.0);
    return dist;
}

class Ticket{
    private:
        float price;
    public:  //we have to do one more thing that if  sou,dest,dot are same then object class me send
        Planet Source;
        Planet Destination;
        Date Date_of_booking;
        Date Date_of_travel;
        string Name; //name of passanger
        string ID; //id of passenger
        //static int Ticket_ID;
        bool Cancel=false; //if the ticket is cancelled then the bool is made true and that cancels ticket 
        bool Return=false; //initially return is by default false //when return ticket has to bee booked this bool is made true


        void Book_ticket(Planet s, Planet d, Date dob, Date dot, string name,string id){
            Source=s;
            Destination=d;
            Date_of_booking=dob;
            Date_of_travel=dot;
            Name=name;
            ID=id;
            set_Price();
            cout<<"Ticket Created"<<endl;
        }

        void Cancel_Ticket(){
            //remove ticket from the vector list_of_ticket
            Cancel=true;
        }

        void Update_Ticket(Planet d,Date dot ){ 
            //there should be some ticket number of each passengers ticket
            Destination=d;
            //as you are updating ticket you must pay for it- it is again calculated using old formula
            // here number of days difference is difference in date of travels
            int no_of_days= getDifference(dot, Date_of_travel);
            price=price+ abs(distance(Source,Destination)*cons/(no_of_days + 1));
            Date_of_travel=dot;
            Cancel=false;
            
        }

        void set_Price(){
            int no_of_days= getDifference(Date_of_booking, Date_of_travel);
            price= distance(Source,Destination)*cons/(no_of_days + 1);
        }

        float Get_Price(){
            return price;
        }
};


class Traveller{
    public: 
        string name;
        string ID;
        vector <Ticket> ticket_list; //have to do here // pending

        string get_name(){
            return name;
        }

        void set_name(string name){
            this->name=name;
        }

        string get_ID(){
            return ID;
        }

        void set_ID(string ID){
            this->ID=ID;
        }

        void update_ID(string new_ID){
            this->ID=new_ID;
        }

        bool verify_ID(string check_ID){
            if(ID == check_ID) return true;
            else return false;
        }

};

class Astronaut:public Traveller{
    private:
        int experience;
    
    public:
        void set_name(string names){
            name=names;
        }

        void set_ID(string Id){
            ID=Id;
        }

        void set_experience(int years){
            experience=years;
        }
        int get_experience(){
            return experience;
        }
};

class Passenger:public Traveller{
    private:
        int validity;

    public:
        void set_name(string names){
            name=names;
        }

        void set_ID(string Id){
            ID=Id;
        }

        void set_validity(int years){
            validity=years;
        }    
        int get_validity(){
            return validity;
        }
};

vector <Passenger> list_of_Passengers;

int pos_tic_pass_tl(vector<Ticket>v,Ticket t){
    int x;
    for(int i=0;i<v.size();i++){
        if(v[i].Name==t.Name) x=i;
    }
    return x;
}
Passenger get_passenger_from_name(string n){
    int x;
    for(int i=0;i<list_of_Passengers.size();i++){
        if(list_of_Passengers[i].name==n) x=i;
    }
    return list_of_Passengers[x];
}

class Commander:public Traveller{
    private:
        //authority
    public:
        void set_name(string names){
            name=names;
        }

        void set_ID(string Id){
            ID=Id;
        }

        int years_of_exp;
        //add more
};

// License ID of Commander
class License_ID:public Commander{

};


//Space Travel Class
class Source_dest_date{
    Planet Source;
    Planet Destination;
    Date date;
    int number_of_pass;
};

class Space_Travel_Class{ //created only when more than two passengers are travelling
    public:
        Planet Source;
        Planet Destination;
        Date dot;
        Astronaut astronaut;
        Commander commander;
        int no_of_passengers; //must be from 3 to 10
        vector <string> list_of_passengers; //names of passengers will be added



        void Add_traveller(string namep){
            list_of_passengers.push_back(namep);
            no_of_passengers++;
        }
        
        //as the astronauts and  commander have ids predefined they gets automatically in the space travel class
        void Set_Astronaut(Astronaut Sir){
            astronaut= Sir;
        }

        void Set_Commander(Commander sir){
            commander=sir;
        }

        void update_Astronaut(Astronaut Sir){
            astronaut= Sir;
        } 

        void update_Commander(Commander sir){
            commander=sir;
        }
        
};

vector <Space_Travel_Class> list_of_stc;

//lets define a global variable in which list of all ticktes are presene
vector < Ticket > all_tickets;


int check(Ticket t){
    int count=0;
    for(int i=0;i<all_tickets.size();i++){
        if(t.Source.name == all_tickets[i].Source.name && t.Destination.name== all_tickets[i].Destination.name && t.Date_of_travel.d == all_tickets[i].Date_of_travel.d && t.Date_of_travel.m == all_tickets[i].Date_of_travel.m && t.Date_of_travel.y == all_tickets[i].Date_of_travel.y){
            count++;
        }
    }
    return count;
}

int no_of_t(Space_Travel_Class s){
    int count=0;
    for(int i=0;i<all_tickets.size();i++){
        if(s.Source.name == all_tickets[i].Source.name && s.Destination.name== all_tickets[i].Destination.name && s.dot.d == all_tickets[i].Date_of_travel.d && s.dot.m == all_tickets[i].Date_of_travel.m && s.dot.y == all_tickets[i].Date_of_travel.y){
            count++;
        }
    }
    return count;
}

// it is  to add passenger in an already existing space travel class
void add_pass(Space_Travel_Class& s){
    for(int i=0;i<all_tickets.size();i++){
        if(s.Source.name == all_tickets[i].Source.name && s.Destination.name== all_tickets[i].Destination.name && s.dot.d == all_tickets[i].Date_of_travel.d && s.dot.m == all_tickets[i].Date_of_travel.m && s.dot.y == all_tickets[i].Date_of_travel.y){
            s.list_of_passengers.push_back(all_tickets[i].Name);
        }
    }
}

//this helps in removing any ticket from vector as it gives me the index
int position_ticket(Ticket t){
    for(int i=0;i<all_tickets.size();i++){
        if(all_tickets[i].Name==t.Name) return i;
    }
    return -1;
}

//it checks ticket in space travel class
void check_ticket_in_stc(Ticket t){
    for(int i=0;i<list_of_stc.size();i++){
         if(t.Source.name==list_of_stc[i].Source.name && t.Destination.name==list_of_stc[i].Destination.name && t.Date_of_travel.d==list_of_stc[i].dot.d && t.Date_of_travel.m==list_of_stc[i].dot.m && t.Date_of_travel.y==list_of_stc[i].dot.y){
           
        }
    }
}

//it prints the requeired ticket
void print_ticket(Ticket t){
    cout<<"----Your Ticket is here----"<<endl;
    cout<<"Name of passenger: "<<t.Name<<endl;
    cout<<"From: "<<t.Source.name<<endl;
    cout<<"To: "<<t.Destination.name<<endl;
    cout<<"Date_of_travel: "<<t.Date_of_travel.d<<"/"<<t.Date_of_travel.m<<"/"<<t.Date_of_travel.y<<endl;
    cout<<"Price of Ticket is: "<<"$"<<t.Get_Price()<<endl;
    if(t.Cancel){
        cout<<"Cancel status: Ticket is cancelled "<<endl;
    }
    else{
        cout<<"Cancel status: No "<<endl;
    }
    cout<<"----Ticket Ends----"<<"\n"<<endl;

}

//it prints space travel class
void print_stc(Space_Travel_Class stc){
    cout<<"----The space travel object details are here----"<<endl;
    cout<<"From: "<<stc.Source.name<<endl;
    cout<<"To: "<<stc.Destination.name<<endl;
    cout<<"Commander: "<<stc.commander.name<<endl;
    cout<<"Astronaut: "<<stc.astronaut.name<<endl;
    cout<<"List of Passengers: "<<endl;
    for(int i=0;i<stc.list_of_passengers.size();i++){
        cout<<stc.list_of_passengers[i]<<endl;
    }
    cout<<"----Space Travel Class ends----"<<"\n"<<endl;
}

//it removes passengers from space travels class member list of passengers
void rem_pass_from_stc(Ticket t,Space_Travel_Class &s){
    for(int i=0;i<s.list_of_passengers.size();i++){
        if(t.Name == s.list_of_passengers[i]){
            s.list_of_passengers.erase(s.list_of_passengers.begin() + i); break;
        }
    }
    s.no_of_passengers--;
}

// it checks whether space travel class has >=3 passengers or not after deletion of some tickets
void check_val_stc(Space_Travel_Class s){
    if(s.no_of_passengers < 3){
        cout<<"Now the spcae travel class has less than 3 passengers so travel is unconfirmed";
    }
}



int main(){

//main code starts

    //My universe
    Hot Uranus;
    Cold Earth;
    Red Mars;
    Earth.atmosphere="The atmosphere is cool and good for humans";
    Earth.water="The water is present in large quantity";
    Earth.name="Earth";
    Uranus.name="Uranus";
    Uranus.atmosphere="The atmosphere is not good for humans";
    Uranus.water="The water is not present at this planet";
    Mars.name="Mars";
    Mars.inhabitant="It is close for humans to be able to live";
    Mars.water="Water is present but at very less quantity";
    Earth.set_coordinates(1,2,3);
    Mars.set_coordinates(3,5,6);
    Uranus.set_coordinates(9,14,19);
    // cout<<distance(Earth,Mars)<<endl;
    //My universe ends

    //name passengers and details
    Passenger Captain_America;
    list_of_Passengers.push_back(Captain_America);
    Captain_America.set_ID("P101");
    Captain_America.set_name("Captain_America");
    Captain_America.set_validity(10);
    Passenger Black_Widow;
    list_of_Passengers.push_back(Black_Widow);
    Black_Widow.set_ID("P102");
    Black_Widow.set_name("Black_Widow");
    Black_Widow.set_validity(13);
    Passenger Black_Panther;
    list_of_Passengers.push_back(Black_Panther);
    Black_Panther.set_ID("P103");
    Black_Panther.set_name("Black_Panther");
    Black_Panther.set_validity(15);
    Passenger Ant_Man;
    list_of_Passengers.push_back(Ant_Man);
    Ant_Man.set_ID("P104");
    Ant_Man.set_name("Ant_Man");
    Ant_Man.set_validity(12);
    Passenger Gamora;
    list_of_Passengers.push_back(Gamora);
    Gamora.set_ID("P105");
    Gamora.set_name("Gamora");
    Gamora.set_validity(20);
    Passenger Thanos;
    list_of_Passengers.push_back(Thanos);
    Thanos.set_ID("P106");
    Thanos.set_name("Thanos");
    Thanos.set_validity(19);
    Passenger Rocket;
    list_of_Passengers.push_back(Rocket);
    Rocket.set_ID("P107");
    Rocket.set_name("Rocket");
    Rocket.set_validity(23);
    Passenger Hawkeye;
    list_of_Passengers.push_back(Hawkeye);
    Hawkeye.set_ID("P108");
    Hawkeye.set_name("Hawkeye");
    Hawkeye.set_validity(6);
    Passenger Deadpool;
    list_of_Passengers.push_back(Deadpool);
    Deadpool.set_ID("P109");
    Deadpool.set_name("Deadpool");
    Deadpool.set_validity(14);
    Passenger Daredevil;
    list_of_Passengers.push_back(Daredevil);
    Daredevil.set_ID("P110");
    Daredevil.set_name("Daredevil");
    Daredevil.set_validity(7);
    Passenger Ms_Marvel;
    list_of_Passengers.push_back(Ms_Marvel);
    Ms_Marvel.set_ID("P111");
    Ms_Marvel.set_name("Ms_Marvel");
    Ms_Marvel.set_validity(25);
    //passengers end

    //name astronauts
    Astronaut Iron_Man;
    Iron_Man.set_name("Iron_Man");
    Iron_Man.set_ID("A101");
    Iron_Man.set_experience(20);
    Astronaut Thor;
    Thor.set_ID("A102");
    Thor.set_name("Thor");
    Thor.set_experience(40);
    //end astronauts

    //name commander
    Commander Hulk;
    Hulk.set_name("Hulk");
    Hulk.set_ID("C101");
    Hulk.years_of_exp=30;
    Commander Spider_Man;
    Spider_Man.set_name("Spider_Name");
    Spider_Man.set_ID("C102");
    Spider_Man.years_of_exp=40;

    //end commander

    //some dates //date2 to date10 are dates of travel and date1 is where bookings open
    Date date1;
    date1.d=2;
    date1.m=12; date1.y=2022;
    Date date2;
    date2.d=23;
    date2.m=3;
    date2.y=2030;
    Date date3;
    date3.d=24;
    date3.m=12;
    date3.y=2033;

    //dates end


//checking of space travel class being created
    //lets book first ticket
    Ticket t1;
    //t1.Book_ticket(Earth,Mars,date1,date2,"Thanos","P269");
    t1.Book_ticket(Earth,Mars,date1,date2,"Thanos","P106");
    Thanos.ticket_list.push_back(t1); //in passengers ticket list the ticket gets added
    
    int no_of_pass;
    no_of_pass=check(t1);

    if(no_of_pass ==2){
        cout<<"Space Travel Object created"<<endl;
    }
    else if(no_of_pass > 2 && no_of_pass<10){
        cout<<"Space Travel Class updated"<<endl;
    }
    else{
        if(no_of_pass <2){
            cout<<"Not enough passengers for Space Travel object to be created!"<<endl;
        }
        else{
            cout<<"Capacity reached already"<<endl;
        }
    }
    if(no_of_pass<10) all_tickets.push_back(t1);
    print_ticket(t1);
    

    Ticket t2;
    t2.Book_ticket(Earth,Mars,date1,date2,"Ant_Man","P104");
    Ant_Man.ticket_list.push_back(t2); //in passengers ticket list the ticket gets added
    
    no_of_pass=check(t2);

    if(no_of_pass ==2){
        cout<<"Space Travel Object created"<<endl;
    }
    else if(no_of_pass > 2 && no_of_pass<10){
        cout<<"Space Travel Class created"<<endl;
        
    }
    else{
        if(no_of_pass <2){
            cout<<"Not enough passengers for Space Travel object to be created!"<<endl;
        }
        else{
            cout<<"capacity reached already"<<endl;
        }
    }
    if(no_of_pass<10) all_tickets.push_back(t2);
    print_ticket(t2);

    Ticket t3;
    t3.Book_ticket(Earth,Mars,date1,date2,"Captain_America","P101");
    Captain_America.ticket_list.push_back(t3); //in passengers ticket list the ticket gets added
    
    no_of_pass=check(t3);
    
    if(no_of_pass ==2){
        cout<<"Space Travel Object created"<<endl;
    }
    else if(no_of_pass > 2 && no_of_pass<10){
        cout<<"Details are updated in space travel"<<endl;
    }
    else{
        if(no_of_pass <2){
            cout<<"Not enough passengers for Space Travel object to be created!"<<endl;
        }
        else{
            cout<<"capacity reached already"<<endl;
        }
    }
    if(no_of_pass<10) all_tickets.push_back(t3);
    print_ticket(t3);

    //the code till here checked that when more than two passengers book same ticket space travel class is created

    //Creating space travel class when the 3rd passenger books
    Space_Travel_Class s1;
    list_of_stc.push_back(s1);
    s1.Set_Astronaut(Thor);
    s1.Set_Commander(Hulk);
    s1.Source = t3.Source;
    s1.Destination = t3.Destination;
    s1.dot=t3.Date_of_travel;
    s1.no_of_passengers= no_of_t(s1);
    add_pass(s1); //here we have to add older 2 passengers also

    //here it ends

    // it checks when a 4th passenger is added then it just adds directly to the space travel object
    Ticket t4;
    t4.Book_ticket(Earth,Mars,date1,date2,"Hawkeye","P108");
    Hawkeye.ticket_list.push_back(t4); //in passengers ticket list the ticket gets added
    no_of_pass=check(t4);
    
    if(no_of_pass ==2){
        cout<<"Space Travel Object created"<<endl;
    }
    else if(no_of_pass > 2 && no_of_pass<10){
        cout<<"Details are updated in space travel"<<endl;
        s1.Add_traveller(t4.Name);
    }
    else{
        if(no_of_pass <2){
            cout<<"Not enough passengers for Space Travel object to be created!"<<endl;
        }
        else{
            cout<<"Capacity reached already"<<endl;
        }
    }
    if(no_of_pass<=10) all_tickets.push_back(t4);

//shows updating astraunaut and commander
    s1.update_Astronaut(Iron_Man);
    cout<<"Updated astronaut of space travel object s1"<<endl;
    s1.update_Commander(Spider_Man);
    cout<<"Updated commander of space travel object s1"<<endl;

    print_stc(s1);


//showing cancelation of ticket
    //lets say t4 has to cancel
    //we have to remove ticket from respective passengers ticket list
    //we have to remove ticket from all ticket list
    //check from space travel object check ticket 
    //remove passenger from space travel if it is

    t4.Cancel_Ticket();
    all_tickets.erase(all_tickets.begin()+ position_ticket(t4)); 
    cout<<"Ticket t4 is deleted!"<<endl;
    rem_pass_from_stc(t4,s1);
    t3.Cancel_Ticket();
    check_val_stc(s1);
    all_tickets.erase(all_tickets.begin()+ position_ticket(t3)); 
    cout<<"Ticket t3 is deleted!"<<endl;
    rem_pass_from_stc(t3,s1);
    check_val_stc(s1);  
    
//end of cancellation of ticket

//lets show updating ticket lets say t3 is updated
    t3.Update_Ticket(Uranus,date3);
    print_ticket(t3);

}

