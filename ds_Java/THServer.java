import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;


public class THServer  implements  Runnable{

    List<ReservationAndCost> ReservationList = new ArrayList<>();
    List<Guest> GuestList = new ArrayList<>();

    //Β μέρος
    List<Guest> WaitList1 = new ArrayList<>();
    List<Guest> WaitList2 = new ArrayList<>();
    List<Guest> WaitList3 = new ArrayList<>();
    List<Guest> WaitList4 = new ArrayList<>();
    List<Guest> WaitList5 = new ArrayList<>();



    public THServer() {
        try {
            THInterface theatre = new THImpl(ReservationList,GuestList,WaitList1,WaitList2,WaitList3,WaitList4,WaitList5);
            // Bind this object instance to the name "RmiServer"

            Naming.rebind("rmi://localhost:9500/Theatre", theatre);
            System.out.println("Theatre bound in registry");
        } catch (Exception e) {
            System.out.println("Trouble: " + e);
        }
    }

    public static void main(String[] args) {
        System.out.println("RMI server started");
	   try { //special exception handler for registry creation

           LocateRegistry.createRegistry(9500);//!!!
           THServer Server=new THServer();
           Thread THThread = new Thread(Server);
           THThread.start();

	               System.out.println("java RMI registry created.");
	       } catch (RemoteException e) {
	       //do nothing, error means registry already exists
	      		  System.out.println("java RMI registry already exists.");
		}


    }

    @Override
    public void run() {
                try {
                    Thread.sleep(50000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

    }
}
