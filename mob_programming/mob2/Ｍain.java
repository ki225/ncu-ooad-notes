import Customer.Customer;
import Video.Video;
import VideoType.Old;
import VideoType.NewRelease;
import VideoType.Children;

class Main {
    public static void main(String[] args) {
        VideoRentalSystem system = new VideoRentalSystem();

        // mob2 情境
        system.addCustomer( new Customer("lunlun") );

        system.addVideo( new Video("緋色的不在場證明", new Old()) );
        system.addVideo( new Video("金剛大戰哥斯拉",  new NewRelease()) );
        system.addVideo( new Video("天線寶寶闖台北",     new Children()) );

        system.rentVideo("lunlun", "緋色的不在場證明", 3);
        system.rentVideo("lunlun", "金剛大戰哥斯拉",   2);
        system.rentVideo("lunlun", "天線寶寶闖台北",   7);

        // 倫倫來店裡想查詢租片記錄        
        system.printCustomerStatement("lunlun");
    }
}