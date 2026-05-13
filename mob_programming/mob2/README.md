# class

VideoRentalSystem
    - List<Customer> customers
    - List<Video> videos
    - List<Rental> rentals             ← 唯一的 Rental 來源
    + rentVideo(customerName, videoName, days)
    + getRentalsByCustomer(name)       ← 由人查
    + getRentalsByVideo(title)         ← 由片查
    + printCustomerStatement(name)     ← 聚合後產報表
    + printVideoRentalHistory(title)   ← 聚合後產報表

Customer                    
    - String name               

Video
- String title
- VideoType type

Rental
    - Customer customer
    - Video video
    - int daysRented
    + getCharge()
    + getPoints()

«abstract» VideoType
    ▲
    ├── Old
    ├── NewRelease
    └── Children

# Compile
```
javac -sourcepath . $(find . -name "*.java") -d out
java -cp out Main
```