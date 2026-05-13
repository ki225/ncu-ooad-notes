package Rental;

import Customer.Customer;
import Video.Video;

public class Rental {
    private Customer customer;
    private Video video;
    private int daysRented;

    public Rental(Customer customer, Video video, int daysRented) {
        this.customer = customer;
        this.video = video;
        this.daysRented = daysRented;
    }

    public Customer getCustomer() { return customer; }
    public Video getVideo() { return video; }
    public int getDaysRented() { return daysRented; }

    public double getCharge() {
        return video.getType().getCharge() * daysRented;
    }

    public int getPoints() {
        return video.getType().getPoints() * daysRented;
    }
}
