package main;

import java.io.File;

public class Demo {
    public static void main(String[] args) {
        VideoConversionFacade converter = new VideoConversionFacade();
        File mp4Video = converter.convertVideo("YouTubeVideo.ogg", "mp4");
        //...
    }
}
