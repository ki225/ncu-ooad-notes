import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import Customer.Customer;
import Video.Video;
import Rental.Rental;

public class VideoRentalSystem {
    private List<Customer> customers = new ArrayList<>();
    private List<Video> videos = new ArrayList<>();
    private List<Rental> rentals = new ArrayList<>();

    public void addCustomer(Customer customer) {
        customers.add(customer);
    }

    public void addVideo(Video video) {
        videos.add(video);
    }

    public void rentVideo(String customerName, String videoName, int days) {
        Customer customer = customers.stream()
            .filter(c -> c.getName().equals(customerName))
            .findFirst()
            .orElseThrow(() -> new RuntimeException("Customer not found: " + customerName));

        Video video = videos.stream()
            .filter(v -> v.getTitle().equals(videoName))
            .findFirst()
            .orElseThrow(() -> new RuntimeException("Video not found: " + videoName));

        rentals.add(new Rental(customer, video, days));

        // 系統顯示獲得常客積點X點，租片費用是X美元
        System.out.println("Customer " + customer.getName() + " earned " + video.getType().getPoints()*days + " frequent renter points, amd charge is $" + video.getType().getCharge()*days);
    }

    public List<Rental> getRentalsByCustomer(String name) {
        return rentals.stream()
            .filter(r -> r.getCustomer().getName().equals(name))
            .collect(Collectors.toList());
    }

    public List<Rental> getRentalsByVideo(String title) {
        return rentals.stream()
            .filter(r -> r.getVideo().getTitle().equals(title))
            .collect(Collectors.toList());
    }

    public void printCustomerStatement(String name) {
        StringBuilder sb = new StringBuilder();
        sb.append("Rental Record for ").append(name).append("\n");

        // 借閱紀錄、每一片花費的價錢 & 花費的總額，以及常客積點的點數總額
        List<Rental> customerRentals = getRentalsByCustomer(name);
        double totalCharge = 0;
        int totalPoints = 0;

        for (Rental r : customerRentals) {
            sb.append("\t").append(r.getVideo().getTitle())
              .append("\t$").append(r.getCharge()).append("\n");
            totalCharge += r.getCharge();
            totalPoints += r.getPoints();
        }

        sb.append("Amount owed is $").append(totalCharge).append("\n");
        sb.append("You earned ").append(totalPoints).append(" frequent renter points");
        
        System.out.println(sb);
    }

    public void printVideoRentalHistory(String title) {
        List<Rental> videoRentals = getRentalsByVideo(title);
        System.out.println("Rental History for \"" + title + "\":");
        for (Rental r : videoRentals) {
            System.out.println("\t" + r.getCustomer().getName()
                + " - " + r.getDaysRented() + " days - $" + r.getCharge());
        }
        System.out.println("Total rentals: " + videoRentals.size());
    }
}
