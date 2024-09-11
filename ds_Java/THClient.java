import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.Naming;
import java.util.ArrayList;
import java.util.List;


public class THClient{

    public static void main(String[] args){

        //List<Guest> GuestList = new ArrayList<>();
        //List<ReservationAndCost> ReservationList = new ArrayList<>();
        try{
            if(args.length==0){
                System.out.println("Πρέπει ανάλογα τη λειτουργία που θέλετε να επιτελέσετε να γράψετε στο command line με έναν από τους 4 τρόπους που παρουσιάζονται παρακάτω:");
                System.out.println("1. java TΗClient list <hostname>");
                System.out.println("2. java TΗClient book <hostname> <type> <number> <name>");
                System.out.println("3. java TΗClient guests <hostname>");
                System.out.println("4. java TΗClient cancel <hostname> <type> <number> <name>:");

            }

            String hostname=args[1];
            //Registry registry=LocateRegistry.getRegistry(hostname);
            //System.setProperty("sun.rmi.transport.tcp.responseTimeout", "5000");
            THInterface theatre=(THInterface) Naming.lookup(
                    "rmi://localhost:9500/Theatre"); //cast sto interface,san to Bank example

            //klisi synartisewn analoga to input sto command line
            String command=args[0];

            if(command.contains("list")){
                String availableSeats=theatre.AvailableSeats();
                System.out.println(availableSeats);

            }else if(command.contains("book")){
                //convert to parameters to their types
                String zone=args[2];
                int number=Integer.parseInt(args[3]); //String->int
                String name=args[4];

                theatre.book(zone,number,name);
                //ReservationAndCost newRes1=theatre.book(zone,number,name);
                //String guestName1=newRes1.getRes().name;
                //Guest guest1=new Guest(guestName1);
                //GuestList.add(guest1);
                //ReservationList.add(newRes1);

            }else if(command.contains("guests")){
                //theatre.ListTheGuests(GuestList);
                theatre.ListTheGuests();
            }else if(command.contains("cancel")){
                //convert to parameters to their types
                String zone=args[2];
                int number=Integer.parseInt(args[3]); //String->int
                String name=args[4];

                theatre.cancel(name,zone,number);

            }

        }catch(Exception e){
            e.printStackTrace();
        }


    }
}
