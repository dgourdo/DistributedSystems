import java.rmi.*;
import java.util.*;

//4 βοηθητικές κλάσεις(Seat,Reservation,Guest,ReservationAndCost)

class Seat implements java.io.Serializable {

    String zone;
    int reservedSeats;
    int cost;

    //constructor
    public Seat(String zone,int reservedSeats,int cost){
        this.zone=zone;
        this.reservedSeats=reservedSeats;
        this.cost=cost;
    }

    //getters
    public String getZone(){
        return zone;
    }

    public int getReservedSeats(){
        return reservedSeats;
    }

    public int getCost(){
        return cost;
    }

}

class Reservation implements java.io.Serializable {

    int numOfSeats;
    String zone;
    String name;

    //constructor
    public Reservation(int numOfSeats,String zone,String name){
        this.numOfSeats=numOfSeats;
        this.zone=zone;
        this.name=name;
    }
}


class Guest implements java.io.Serializable {

    String name;
    List<Reservation> reservations;


    //constructor
    public Guest(String name){
        this.name=name;
        this.reservations=new ArrayList<>();
    }

    //getters
   public  String getName(){
        return name;
    }

}


class ReservationAndCost implements java.io.Serializable {

    Reservation res;
    int cost;

    //constructor
    public ReservationAndCost(Reservation res,int cost){
        this.res=res;
        this.cost=cost;
    }

    //getters
    public Reservation getRes(){
        return res;
    }


    public int getCost(){
        return cost;
    }

}


public class THImpl extends java.rmi.server.UnicastRemoteObject implements THInterface {

    static final int maxSize1 = 100;
    static final int maxSize2 = 200;
    static final int maxSize3 = 400;
    static final int maxSize4 = 225;
    static final int maxSize5 = 75;

    Seat Seat1;
    Seat Seat2;
    Seat Seat3;
    Seat Seat4;
    Seat Seat5;

    //Λίστες:οριζονται με τετοιο τροπο ωστε να μη χρειαζεται να τις περασουμε ως ορισμα στις μεθοδους του προγραμματος.
    //Πολυ σημαντικες για τη λειτουργια του προγραμματος οι 2 παρακατω λιστες.
    private List<ReservationAndCost> finalRes;
    private List<Guest> GuestList;

    //Β μερος
    private List<Guest> WaitList1;
    private List<Guest> WaitList2;
    private List<Guest> WaitList3;
    private List<Guest> WaitList4;
    private List<Guest> WaitList5;



    public THImpl(List<ReservationAndCost> finalRes,List<Guest> GuestList,List<Guest> WaitList1,List<Guest> WaitList2,List<Guest> WaitList3,List<Guest> WaitList4,List<Guest> WaitList5) //constructor tou remote antikeimenou
            throws java.rmi.RemoteException {
        super(); //kalei ton constructor tou patera
        this.finalRes=finalRes;
        this.GuestList=GuestList;
        this.WaitList1=WaitList1;
        this.WaitList2=WaitList2;
        this.WaitList3=WaitList3;
        this.WaitList4=WaitList4;
        this.WaitList5=WaitList5;


        //Σεναριο:Εχουν ηδη πωληθει ορισμενα εισητηρια
        Seat1 = new Seat("ΠΑ", 10, 45);
        Seat2 = new Seat("ΠΒ", 50, 35);
        Seat3 = new Seat("ΠΓ", 222, 25);
        Seat4 = new Seat("ΚΕ", 55, 30);
        Seat5 = new Seat("ΠΘ", 60, 20);

    }

    int availableSeats1;
    int availableSeats2;
    int availableSeats3;
    int availableSeats4;
    int availableSeats5;

    public synchronized String AvailableSeats() throws java.rmi.RemoteException {

        availableSeats1 = maxSize1 - Seat1.getReservedSeats();
        availableSeats2 = maxSize2 - Seat2.getReservedSeats();
        availableSeats3 = maxSize3 - Seat3.getReservedSeats();
        availableSeats4 = maxSize4 - Seat4.getReservedSeats();
        availableSeats5 = maxSize5 - Seat5.getReservedSeats();


        return (availableSeats1 + " " + "θέσεις" + " " + "Πλατεία - Ζώνη Α (κωδικός: " + Seat1.getZone() + ") - τιμή: " + " " + Seat1.getCost() + " Ευρώ" + "\n" + availableSeats2 + " " + "θέσεις" + " " + "Πλατεία - Ζώνη Β (κωδικός: " + Seat2.getZone() + ") - τιμή: " + " " + Seat2.getCost() + " Ευρώ" + "\n" + availableSeats3 + " " + "θέσεις" + " " + "Πλατεία - Ζώνη Γ (κωδικός: " + Seat3.getZone() + ") - τιμή: " + " " + Seat3.getCost() + " Ευρώ" + "\n" + availableSeats4 + " " + "θέσεις" + " " + "Κεντρικός Εξώστης (κωδικός: " + Seat4.getZone() + ") - τιμή: " + " " + Seat4.getCost() + " Ευρώ" + "\n" + availableSeats5 + " " + "θέσεις" + " " + "Πλαϊνά Θεωρεία (κωδικός: " + Seat5.getZone() + ") - τιμή: " + " " + Seat5.getCost() + " Ευρώ");

    }


    public synchronized ReservationAndCost book(String zone, int number, String name) throws RemoteException {

        Reservation Reservation = new Reservation(number, zone, name);
        int costOfRes = 0;
        ReservationAndCost ReservationAndCost = new ReservationAndCost(Reservation, costOfRes); //!!!

        switch (zone) {
            case "ΠΑ":
                if (number <= availableSeats1) {
                    availableSeats1 -= number;
                    costOfRes = number * Seat1.getCost();
                    finalRes.add(ReservationAndCost); //!!!

                    Guest Guest = new Guest(name);
                    if (!GuestList.contains(Guest))
                        GuestList.add(Guest);

                    System.out.println("Επιτυχής κράτηση!");
                    System.out.println("Συνολικό κόστος: " + costOfRes);

                } else {
                    //get client's input
                    Scanner sc = new Scanner(System.in);
                    System.out.println("Δυστυχώς βρέθηκαν λιγότερες θέσεις από αυτές που ζητήσατε.Διαθέσιμες θέσεις: " + availableSeats1 + "Τις θέλετε?Press 'y' or 'n'.");
                    char a = sc.next().charAt(0);
                    if (a == 'y') {
                        availableSeats1 -= number;
                        costOfRes = number * Seat1.getCost();
                        finalRes.add(ReservationAndCost);

                        Guest Guest = new Guest(name);
                        if (!GuestList.contains(Guest))
                            GuestList.add(Guest);

                        System.out.println("Επιτυχής κράτηση!");
                        System.out.println("Συνολικό κόστος: " + costOfRes);

                    } else {
                        System.out.println("Αποτυχία.");

                        //Β μερος
                        System.out.println("Θέλετε να εγγραφείτε σε λίστα αναμονής,σε περίπτωση ακύρωσης,στη συγκεκριμένη ζώνη?Press 'y' or 'n'.");
                        char b = sc.next().charAt(0);
                        if (b == 'y') {
                            Guest Guest = new Guest(name);
                            if (!WaitList1.contains(Guest))
                                WaitList1.add(Guest);
                    }
                }}
                break;


            case "ΠΒ":
                if (number <= availableSeats2) {
                    availableSeats2 -= number;
                    costOfRes = number * Seat2.getCost();
                    finalRes.add(ReservationAndCost);

                    Guest Guest = new Guest(name);
                    if (!GuestList.contains(Guest))
                        GuestList.add(Guest);

                    System.out.println("Επιτυχής κράτηση!");
                    System.out.println("Συνολικό κόστος: " + costOfRes);

                } else {
                    //get client's input
                    Scanner sc = new Scanner(System.in);
                    System.out.println("Δυστυχώς βρέθηκαν λιγότερες θέσεις από αυτές που ζητήσατε.Διαθέσιμες θέσεις: " + availableSeats2 + "Τις θέλετε?Press 'y' or 'n'.");
                    char a = sc.next().charAt(0);
                    if (a == 'y') {
                        availableSeats2 -= number;
                        costOfRes = number * Seat2.getCost();
                        finalRes.add(ReservationAndCost);

                        Guest Guest = new Guest(name);
                        if (!GuestList.contains(Guest))
                            GuestList.add(Guest);

                        System.out.println("Επιτυχής κράτηση!");
                        System.out.println("Συνολικό κόστος: " + costOfRes);

                    } else {
                        System.out.println("Αποτυχία.");

                        //Β μερος
                        System.out.println("Θέλετε να εγγραφείτε σε λίστα αναμονής,σε περίπτωση ακύρωσης,στη συγκεκριμένη ζώνη?Press 'y' or 'n'.");
                        char b = sc.next().charAt(0);
                        if (b == 'y') {
                            Guest Guest = new Guest(name);
                            if (!WaitList2.contains(Guest))
                                WaitList2.add(Guest);
                        }
                    }
                }
                break;


            case "ΠΓ":
                if (number <= availableSeats3) {
                    availableSeats3 -= number;
                    costOfRes = number * Seat3.getCost();
                    finalRes.add(ReservationAndCost);

                    Guest Guest = new Guest(name);
                    if (!GuestList.contains(Guest))
                        GuestList.add(Guest);

                    System.out.println("Επιτυχής κράτηση!");
                    System.out.println("Συνολικό κόστος: " + costOfRes);

                } else {
                    //get client's input
                    Scanner sc = new Scanner(System.in);
                    System.out.println("Δυστυχώς βρέθηκαν λιγότερες θέσεις από αυτές που ζητήσατε.Διαθέσιμες θέσεις: " + availableSeats3 + "Τις θέλετε?Press 'y' or 'n'.");
                    char a = sc.next().charAt(0);
                    if (a == 'y') {
                        availableSeats3 -= number;
                        costOfRes = number * Seat3.getCost();
                        finalRes.add(ReservationAndCost);

                        Guest Guest = new Guest(name);
                        if (!GuestList.contains(Guest))
                            GuestList.add(Guest);

                        System.out.println("Επιτυχής κράτηση!");
                        System.out.println("Συνολικό κόστος: " + costOfRes);

                    } else {
                        System.out.println("Αποτυχία.");

                        //Β μερος
                        System.out.println("Θέλετε να εγγραφείτε σε λίστα αναμονής,σε περίπτωση ακύρωσης,στη συγκεκριμένη ζώνη?Press 'y' or 'n'.");
                        char b = sc.next().charAt(0);
                        if (b == 'y') {
                            Guest Guest = new Guest(name);
                            if (!WaitList3.contains(Guest))
                                WaitList3.add(Guest);
                        }
                    }
                }
                break;


            case "ΚΕ":
                if (number <= availableSeats4) {
                    availableSeats4 -= number;
                    costOfRes = number * Seat4.getCost();
                    finalRes.add(ReservationAndCost);

                    Guest Guest = new Guest(name);
                    if (!GuestList.contains(Guest))
                        GuestList.add(Guest);

                    System.out.println("Επιτυχής κράτηση!");
                    System.out.println("Συνολικό κόστος: " + costOfRes);

                } else {
                    //get client's input
                    Scanner sc = new Scanner(System.in);
                    System.out.println("Δυστυχώς βρέθηκαν λιγότερες θέσεις από αυτές που ζητήσατε.Διαθέσιμες θέσεις: " + availableSeats4 + "Τις θέλετε?Press 'y' or 'n'.");
                    char a = sc.next().charAt(0);
                    if (a == 'y') {
                        availableSeats4 -= number;
                        costOfRes = number * Seat4.getCost();
                        finalRes.add(ReservationAndCost);

                        Guest Guest = new Guest(name);
                        if (!GuestList.contains(Guest))
                            GuestList.add(Guest);

                        System.out.println("Επιτυχής κράτηση!");
                        System.out.println("Συνολικό κόστος: " + costOfRes);

                    } else {
                        System.out.println("Αποτυχία.");

                        //Β μερος
                        System.out.println("Θέλετε να εγγραφείτε σε λίστα αναμονής,σε περίπτωση ακύρωσης,στη συγκεκριμένη ζώνη?Press 'y' or 'n'.");
                        char b = sc.next().charAt(0);
                        if (b == 'y') {
                            Guest Guest = new Guest(name);
                            if (!WaitList4.contains(Guest))
                                WaitList4.add(Guest);
                        }
                    }
                }
                break;


            case "ΠΘ":
                if (number <= availableSeats5) {
                    availableSeats5 -= number;
                    costOfRes = number * Seat5.getCost();
                    finalRes.add(ReservationAndCost);

                    Guest Guest = new Guest(name);
                    if (!GuestList.contains(Guest))
                        GuestList.add(Guest);

                    System.out.println("Επιτυχής κράτηση!");
                    System.out.println("Συνολικό κόστος: " + costOfRes);

                } else {
                    //get client's input
                    Scanner sc = new Scanner(System.in);
                    System.out.println("Δυστυχώς βρέθηκαν λιγότερες θέσεις από αυτές που ζητήσατε.Διαθέσιμες θέσεις: " + availableSeats5 + "Τις θέλετε?Press 'y' or 'n'.");
                    char a = sc.next().charAt(0);
                    if (a == 'y') {
                        availableSeats5 -= number;
                        costOfRes = number * Seat5.getCost();
                        finalRes.add(ReservationAndCost);

                        Guest Guest = new Guest(name);
                        if (!GuestList.contains(Guest))
                            GuestList.add(Guest);

                        System.out.println("Επιτυχής κράτηση!");
                        System.out.println("Συνολικό κόστος: " + costOfRes);

                    } else {
                        System.out.println("Αποτυχία.");

                        //Β μερος
                        System.out.println("Θέλετε να εγγραφείτε σε λίστα αναμονής,σε περίπτωση ακύρωσης,στη συγκεκριμένη ζώνη?Press 'y' or 'n'.");
                        char b = sc.next().charAt(0);
                        if (b == 'y') {
                            Guest Guest = new Guest(name);
                            if (!WaitList5.contains(Guest))
                                WaitList5.add(Guest);
                        }
                    }
                }
                break;
        }

        return ReservationAndCost;
    }

    public synchronized void ListTheGuests() throws java.rmi.RemoteException {
        int i = 0;
        for (Guest g : GuestList) {//for-each
            System.out.println(++i + ") " + g.name);
            for (ReservationAndCost rc : finalRes) {
                if (rc.getRes().name.equals(g.name)) {
                    System.out.println(rc.getRes().numOfSeats + " " + rc.getRes().zone + " " + rc.getCost());
                }
            }
        }
    }

    public synchronized void cancel(String name, String zone, int number) throws java.rmi.RemoteException {
        for (Guest g : GuestList) {
            if (name.equals(g.getName())) {
                System.out.println("Δεν έχετε κάνει κάποια κράτηση.");
            } else {
                for (ReservationAndCost res : finalRes) {
                    if ((((res.getRes().name.equals(name))) || (res.getRes().zone.equals(zone)))) {
                        System.out.println("Δεν έχετε κάνει κάποια κράτηση στο συγκεκριμένο τύπο θέσης.");
                    } else {
                        if (!(((res.getRes().name.equals(name))) || (res.getRes().numOfSeats >= number))) {
                            System.out.println("Δεν έχετε κάνει κάποια κράτηση για το συγκεκριμένο αριθμό θέσεων.");
                        } else {
                            if (res.getRes().numOfSeats > number) {
                                finalRes.remove(res);
                                res.getRes().numOfSeats = res.getRes().numOfSeats - number;
                                finalRes.add(res);
                            } else {
                                //-------------------------------------------------------
                                //Β μερος
                                String flag=res.getRes().zone;
                                switch (flag){
                                    case "ΠΑ":
                                        for(Guest guest: WaitList1){
                                            //print a message to the THClient's screen
                                            System.out.println("Κυρία/Κύριε "+guest.getName()+",σας ειδοποιούμε ότι υπάρχουν κάποιες θέσεις στο Θέατρο, για τον τύπο θέσης που επιθυμείτε.");
                                        }
                                        break;

                                    case "ΠB":
                                        for(Guest guest: WaitList2){
                                            System.out.println("Κυρία/Κύριε "+guest.getName()+",σας ειδοποιούμε ότι υπάρχουν κάποιες θέσεις στο Θέατρο, για τον τύπο θέσης που επιθυμείτε.");
                                        }
                                        break;

                                    case "ΠΓ":
                                        for(Guest guest: WaitList3){
                                            System.out.println("Κυρία/Κύριε "+guest.getName()+",σας ειδοποιούμε ότι υπάρχουν κάποιες θέσεις στο Θέατρο, για τον τύπο θέσης που επιθυμείτε.");
                                        }
                                        break;

                                    case "ΚΕ":
                                        for(Guest guest: WaitList4){
                                            System.out.println("Κυρία/Κύριε "+guest.getName()+",σας ειδοποιούμε ότι υπάρχουν κάποιες θέσεις στο Θέατρο, για τον τύπο θέσης που επιθυμείτε."
                                            );}
                                        break;

                                    case "ΠΘ":
                                        for(Guest guest: WaitList5){
                                            System.out.println("Κυρία/Κύριε "+guest.getName()+",σας ειδοποιούμε ότι υπάρχουν κάποιες θέσεις στο Θέατρο, για τον τύπο θέσης που επιθυμείτε.");
                                        }
                                        break;
                                }

                                //-------------------------------------------------------

                                finalRes.remove(res);
                                String nm = res.getRes().name;

                                if (nm != null) {
                                    int j = 0;
                                    for (ReservationAndCost rc : finalRes) {
                                        System.out.println(++j + ". ");
                                        if (rc.getRes().name.equals(name)) {
                                            System.out.println(rc.getRes().numOfSeats + " " + rc.getRes().zone + " " + rc.getCost());
                                        }
                                    }
                                } else {
                                    GuestList.remove(g);
                                }
                            }
                        }
                    }
                }
            }
        }

    }

}








