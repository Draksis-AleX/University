public class Demo {
    public static void main(String[] args) {

        Logger logger = createChain();

        logger.logMessage(1, "Messaggio Livello 1 (Standard info)");
        logger.logMessage(2, "Messaggio Livello 2 (Debug)");
        logger.logMessage(3, "Messaggio Livello 3 (Error)");
        
    }

    public static Logger createChain(){
        Logger standardLogger = new ConsoleLogger(AbstractLogger.INFO);
        Logger fileLogger = new FileLogger(AbstractLogger.DEBUG);
        Logger errorLogger = new ErrorLogger(AbstractLogger.ERROR);

        errorLogger.setNextLogger(fileLogger);
        fileLogger.setNextLogger(standardLogger);
        
        return errorLogger;
    }
}
