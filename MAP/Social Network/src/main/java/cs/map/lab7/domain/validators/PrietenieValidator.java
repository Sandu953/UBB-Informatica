package cs.map.lab7.domain.validators;


import cs.map.lab7.domain.Prietenie;

import java.time.LocalDate;

public class PrietenieValidator implements Validator<Prietenie>{
    @Override
    public void validate(Prietenie prietenie) throws ValidationException{
        long IdPrieten1 = prietenie.getId().getLeft();
        long IdPrieten2 = prietenie.getId().getRight();
        if(IdPrieten1==IdPrieten2)throw new ValidationException("a friendship cannot be between the same person");
        if(prietenie.getDate().isAfter(LocalDate.now()))throw new ValidationException("invalide friendship date");

    }
}