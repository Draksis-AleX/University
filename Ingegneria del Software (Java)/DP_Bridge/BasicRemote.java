public class BasicRemote implements Remotes{
    
    protected Device device;

    public BasicRemote() {}

    public BasicRemote(Device device) { this.device = device; }

    @Override
    public void power() {
        System.out.println("Remote: power toggle");
        if (device.isEnabled()) device.disable();
        else device.enable();
    }

    @Override
    public void volumeDown() {
        System.out.println("Remote: Volume Down");
        device.setVolume(device.getVolume() - 10);
    }

    @Override
    public void volumeUp() {
        System.out.println("Remote: Volume Up");
        device.setVolume(device.getVolume() + 10);
    }

    @Override
    public void channelDown() {
        System.out.println("Remote: Channel Down");
        device.setVolume(device.getChannel() - 1);
    }

    @Override
    public void channelUp() {
        System.out.println("Remote: Channel Up");
        device.setVolume(device.getChannel() + 1);
    }
}
