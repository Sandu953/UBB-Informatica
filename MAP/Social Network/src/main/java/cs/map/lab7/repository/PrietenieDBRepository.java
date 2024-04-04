package cs.map.lab7.repository;


import cs.map.lab7.domain.Prietenie;
import cs.map.lab7.domain.Tuple;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Optional;

public class PrietenieDBRepository implements Repository<Tuple<Long, Long>, Prietenie> {

    private final String Url;
    private final String User;
    private final String Password;

    public PrietenieDBRepository(String url, String user, String password) {
        this.Url = url;
        this.Password = password;
        this.User = user;
    }

    @Override
    public Optional<Prietenie> findOne(Tuple<Long, Long> longLongTuple) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement1 = connection.prepareStatement(
                     "select * from friendships where id1=? AND id2 =?");
             PreparedStatement statement2 = connection.prepareStatement(
                     "select * from friendships where id1=? AND id2 =?")) {

            statement1.setInt(1, Math.toIntExact(longLongTuple.getLeft()));
            statement1.setInt(2, Math.toIntExact(longLongTuple.getRight()));
            ResultSet resultSet = statement1.executeQuery();
            if (!resultSet.next()) {
                statement2.setInt(1, Math.toIntExact(longLongTuple.getRight()));
                statement2.setInt(2, Math.toIntExact(longLongTuple.getLeft()));
                ResultSet resultSet1 = statement2.executeQuery();
                if (resultSet1.next()) {
                    var dt = resultSet1.getDate("friendsfrom").toLocalDate();
                    Prietenie prietenie = new Prietenie(dt, longLongTuple.getLeft(),
                            longLongTuple.getRight());
                    return Optional.ofNullable(prietenie);
                }
            } else {
                var dt = resultSet.getDate("friendsfrom").toLocalDate();
                Prietenie prietenie = new Prietenie(dt, longLongTuple.getLeft(),
                        longLongTuple.getRight());
                return Optional.ofNullable(prietenie);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Prietenie> findAll() {
        ArrayList<Prietenie> prietenieSet = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from friendships");
        ) {
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");
                var dt = resultSet.getDate("friendsfrom").toLocalDate();
                Prietenie prietenie = new Prietenie(dt, id1, id2);
                prietenieSet.add(prietenie);
            }
            return prietenieSet;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Prietenie> save(Prietenie entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "insert into friendships(id1,id2,friendsfrom) values (?,?,?)")
        ) {
            var id1 = entity.getId().getLeft();
            var id2 = entity.getId().getRight();
            statement.setInt(1, Math.toIntExact(id1));
            statement.setInt(2, Math.toIntExact(id2));
            var dt = LocalDate.of(
                    entity.getDate().getYear(), entity.getDate().getMonthValue(),
                    entity.getDate().getDayOfMonth());
            statement.setDate(3, Date.valueOf(dt));
            statement.executeUpdate();
            return Optional.empty();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Prietenie> delete(Tuple<Long, Long> longLongTuple) {
        try (Connection connection2 = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement2 = connection2.prepareStatement(
                     "DELETE FROM friendships WHERE id1 = ? and id2 = ?");) {
            var cv = findOne(longLongTuple);
            statement2.setLong(1, longLongTuple.getLeft());
            statement2.setLong(2, longLongTuple.getRight());

            int affectedRows = statement2.executeUpdate();

            statement2.executeUpdate();
            return affectedRows == 0 ? Optional.empty() : cv;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Prietenie> update(Prietenie entity) {
        return Optional.empty();
    }
}
