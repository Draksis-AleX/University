public class AdvancedRemote extends BasicRemote {

public AdvancedRemote(Device device) { this.device = device; }

    public void mute() {
        System.out.println("Remote: Mute");
        device.setVolume(0);
    }
    
}
