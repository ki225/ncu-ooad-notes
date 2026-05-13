package Video;

import VideoType.VideoType;

public class Video {
    private String title;
    private VideoType type;

    public Video(String title, VideoType type) {
        this.title = title;
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public VideoType getType() {
        return type;
    }
}
