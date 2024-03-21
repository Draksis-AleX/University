package main;

import java.io.File;

import complex_media_library.*;


public class VideoConversionFacade {

    public File convertVideo(String filename, String format) {

        System.out.println("Video Converter: Conversion Started...");

        VideoFile file = new VideoFile(filename);
        Codec sourceCodec = CodecFactory.extract(file);
        Codec destinationCodec;

        if (format.equals("mp4")) destinationCodec = new MPEG4CompressionCodec();
        else destinationCodec = new OggCompressionCodec();

        VideoFile buffer = BitrateReader.read(file, sourceCodec);
        VideoFile intermediateResult = BitrateReader.convert(buffer, destinationCodec);

        File result = new AudioMixer().fix(intermediateResult);

        System.out.print("Video Converter: Conversion Comleted.");

        return result;
        
    }
    
}
