package cs.map.lab7.repository;

import cs.map.lab7.domain.Message;
import cs.map.lab7.domain.Utilizator;
import cs.map.lab7.repository.UtilizatorDBRepository;

import java.sql.*;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class MessageDBRepository implements Repository<Long, Message> {
    private final UtilizatorDBRepository repoUtilizator;
    private final String Url;
    private final String User;
    private final String Password;

    public MessageDBRepository(String url, String user, String password, UtilizatorDBRepository repository) {
        this.Url = url;
        this.Password = password;
        this.User = user;
        this.repoUtilizator = repository;
    }

    @Override
    public Optional<Message> findOne(Long aLong) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from messages where id = ?;");) {
            statement.setInt(1, Math.toIntExact(aLong));
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                Long id_from = resultSet.getLong("id_from");
                List<String> list_to = Arrays.stream(resultSet.getString("id_to").split(",")).toList();
                List<Utilizator> list_user = new ArrayList<>();
                for (String s : list_to) {
                    list_user.add(repoUtilizator.findOne(Long.parseLong(s)).get());
                }
                String mesaj = resultSet.getString("mesaj");
                LocalDateTime date = resultSet.getTimestamp("mesaj_from").toLocalDateTime();
                Long reply = resultSet.getLong("reply");
                Message m = new Message(repoUtilizator.findOne(id_from).get(), list_user, mesaj, date);
                if(reply != -1)
                    m.setReply(findOne(reply).get());
                m.setId(aLong);
                return Optional.ofNullable(m);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<Message> findAll() {
        ArrayList<Message> mesaje = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from messages;");) {
            ResultSet resultSet = statement.executeQuery();
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                Long id_from = resultSet.getLong("id_from");
                List<String> list_to = Arrays.stream(resultSet.getString("id_to").split(",")).toList();
                List<Utilizator> list_user = new ArrayList<>();
                for (String s : list_to) {
                    list_user.add(repoUtilizator.findOne(Long.parseLong(s)).get());
                }
                String mesaj = resultSet.getString("mesaj");
                LocalDateTime date = resultSet.getTimestamp("mesaj_from").toLocalDateTime();
                Long reply = resultSet.getLong("reply");
                Message m = new Message(repoUtilizator.findOne(id_from).get(), list_user, mesaj, date);
                if(reply != -1){
                    m.setReply(findOne(reply).get());
                }
                m.setId(id);
                mesaje.add(m);
            }
            return mesaje;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Message> save(Message entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement =
                connection.prepareStatement("insert into messages(id,id_from,id_to,mesaj,mesaj_from,reply)values (?,?,?,?,?,?);");) {
            statement.setInt(1, Math.toIntExact(entity.getId()));
            statement.setInt(2, Math.toIntExact(entity.getFrom().getId()));
            String tu = "";
            for(Utilizator u:entity.getTo()){
                tu = tu + u.getId().toString() + ',';
            }
            statement.setString(3, tu.substring(0,tu.length() - 1));
            statement.setString(4, entity.getMessage());
            var dt = LocalDateTime.of(
                    entity.getData().getYear(), entity.getData().getMonthValue(),
                    entity.getData().getDayOfMonth(), entity.getData().getHour(),
                    entity.getData().getMinute(),entity.getData().getSecond());
            statement.setTimestamp(5,Timestamp.valueOf(dt));
            statement.setInt(6,-1);
            statement.executeUpdate();

            return Optional.empty();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Message> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<Message> update(Message entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "update messages set reply = ? where id = ?");) {
            statement.setInt(1, Math.toIntExact(entity.getReply().getId()));
            statement.setInt(2, Math.toIntExact(entity.getId()));
            statement.executeUpdate();

            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
