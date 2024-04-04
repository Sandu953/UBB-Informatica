package cs.map.lab7.domain;


import java.util.List;
import java.util.Objects;

public class Utilizator extends cs.map.lab7.domain.Entity<Long> {
    private String firstName;
    private String lastName;
    private String username;
    private String password;

    /**
     * construnctor
     *
     * @param firstName String
     * @param lastName  String
     */
    public Utilizator(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /**
     * @return the firstname
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * set the firstName
     *
     * @param firstName String
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * return LastName
     *
     * @return String
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * set lastname
     *
     * @param lastName String
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername() {
        this.username = firstName + '_' + lastName + getId();
    }

    public String getPassword() {
        return password;
    }

    public void setPassword() {
        this.password = "Parola" + getId();
    }

    /**
     * override toString
     *
     * @return String
     */
    @Override
    public String toString() {
        return "Utilizator{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                '}';
    }

    /**
     * override equals
     *
     * @param o Object
     * @return boolean
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator that)) return false;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());// &&
        //getFriends().equals(that.getFriends());
    }

    /**
     * override hashcode
     *
     * @return int
     */
    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName());
    }
}