public interface Logger {
    public void setNextLogger(Logger logger);
    public void logMessage(int level, String message);
}