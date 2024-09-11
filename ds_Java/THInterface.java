import java.util.List;

public interface THInterface extends java.rmi.Remote{

    String AvailableSeats() throws java.rmi.RemoteException;
    ReservationAndCost book(String zone,int number,String name) throws java.rmi.RemoteException;
    void ListTheGuests() throws java.rmi.RemoteException;
    void cancel(String name,String zone,int number) throws java.rmi.RemoteException;
}
