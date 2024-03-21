public abstract class AbstractLogger implements Logger{
    public final static int INFO = 1;
    public final static int DEBUG = 2;
    public final static int ERROR = 3;

    protected int level;

    protected Logger nextLogger;

    public void setNextLogger(Logger logger) { this.nextLogger = logger; }

    public void logMessage(int level, String message) {
        if (this.level <= level) write(message);
        else if (this.nextLogger != null) nextLogger.logMessage(level, message);
    }

    public abstract void write(String message);
}
