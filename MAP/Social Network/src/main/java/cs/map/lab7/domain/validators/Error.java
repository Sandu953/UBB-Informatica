package cs.map.lab7.domain.validators;


public class Error extends RuntimeException {
    private final String message;
    public Error(String message){this.message=message;}
    @Override
    public String getMessage() {
        return message;
    }
}