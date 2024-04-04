package cs.map.lab7.domain.validators;

@FunctionalInterface
public interface Validator<T> {
    void validate(T entity) throws cs.map.lab7.domain.validators.ValidationException;
}