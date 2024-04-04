package cs.map.lab7.repository;
import cs.map.lab7.domain.Utilizator;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import java.sql.*;
import java.util.ArrayList;
import java.util.Base64;
import java.util.List;
import java.util.Optional;

public class UtilizatorDBRepository implements PagingRepository<Long, Utilizator> {

    private String Url;
    private String User;
    private String Password;

    private SecretKey secretKey;

    public UtilizatorDBRepository(String url, String user, String password, SecretKey secretKey) {
        this.Url = url;
        this.User = user;
        this.Password = password;
        this.secretKey = secretKey;
    }

    @Override
    public Optional<Utilizator> findOne(Long aLong) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from users where id = ?;");) {
            statement.setInt(1, Math.toIntExact(aLong));
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                Utilizator utilizator = new Utilizator(firstName, lastName);
                utilizator.setId(aLong);
                utilizator.setPassword();
                utilizator.setUsername();
                return Optional.ofNullable(utilizator);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    public boolean findOneUserName(String username, String password) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from users where username = ?;");) {
            statement.setString(1,username);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                String parola = resultSet.getString("password");
                return decriptare(parola, secretKey).equals(password);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return false;
    }


    @Override
    public Iterable<Utilizator> findAll() {
        ArrayList<Utilizator> utilizators = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from users"); ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                Utilizator utilizator = new Utilizator(firstName, lastName);
                utilizator.setId(id);
                utilizator.setPassword();
                utilizator.setUsername();
                utilizators.add(utilizator);
            }
            return utilizators;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password); PreparedStatement statement =
                connection.prepareStatement("insert into users(id,first_name,last_name,username,password)values (?,?,?,?,?);");) {
            statement.setInt(1, Math.toIntExact(entity.getId()));
            statement.setString(2, entity.getFirstName());
            statement.setString(3, entity.getLastName());
            statement.setString(4, entity.getUsername());
            statement.setString(5, criptare(entity.getPassword(), secretKey) );
            statement.executeUpdate();

            return Optional.empty();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    public ArrayList<Utilizator> getUsersString(final String caractere) {
        ArrayList<Utilizator> utilizators = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(Url, User, Password); PreparedStatement statement =
                connection.prepareStatement("select * from users where last_name like ?;")) {
            statement.setString(1, '%' + caractere + '%');
            try (ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    Long id = resultSet.getLong("id");
                    String firstName = resultSet.getString("first_name");
                    String lastName = resultSet.getString("last_name");
                    Utilizator utilizator = new Utilizator(firstName, lastName);
                    utilizator.setId(id);
                    utilizator.setPassword();
                    utilizator.setUsername();
                    utilizators.add(utilizator);
                }
                return utilizators;
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<Utilizator> delete(Long aLong) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement("DELETE FROM users WHERE ID = ?");) {
            var cv = findOne(aLong);
            statement.setLong(1, aLong);
            int affectedRows = statement.executeUpdate();
            try (Connection connection2 = DriverManager.getConnection(Url, User, Password);
                 PreparedStatement statement2 = connection2.prepareStatement("DELETE FROM friendships WHERE id1 = ? or id2 = ?");) {

                statement2.setLong(1, aLong);
                statement2.setLong(2, aLong);

                statement2.executeUpdate();

            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            return affectedRows == 0 ? Optional.empty() : cv;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public Optional<Utilizator> update(Utilizator entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "update users set first_name = ?, last_name = ?, username = ?, password = ? where id = ?");) {
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setString(3, entity.getUsername());
            statement.setString(4, criptare(entity.getPassword(), secretKey));
            statement.setInt(5, Math.toIntExact(entity.getId()));
            statement.executeUpdate();

            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public Page<Utilizator> findAll(Pageable pageable) {
        List<Utilizator> utilizators = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(this.Url, this.User, this.Password);
             PreparedStatement pagePreparedStatement = connection.prepareStatement("SELECT * FROM users " +
                     "LIMIT ? OFFSET ?");

             PreparedStatement countPreparedStatement = connection.prepareStatement
                     ("SELECT COUNT(*) AS count FROM users ");

        ) {
            pagePreparedStatement.setInt(1, pageable.getPageSize());
            pagePreparedStatement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            try (ResultSet pageResultSet = pagePreparedStatement.executeQuery();
                 ResultSet countResultSet = countPreparedStatement.executeQuery();) {
                while (pageResultSet.next()) {
                    Long id = pageResultSet.getLong("id");
                    String firstName = pageResultSet.getString("first_name");
                    String lastName = pageResultSet.getString("last_name");
                    Utilizator utilizator = new Utilizator(firstName, lastName);
                    utilizator.setId(id);
                    utilizator.setPassword();
                    utilizator.setUsername();
                    utilizators.add(utilizator);
                }
                int totalCount = 0;
                if (countResultSet.next()) {
                    totalCount = countResultSet.getInt("count");
                }

                return new Page<>(utilizators, totalCount);

            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static String criptare(String text, SecretKey secretKey) throws Exception {
        Cipher cipher = Cipher.getInstance("AES");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        byte[] textCriptat = cipher.doFinal(text.getBytes());
        return Base64.getEncoder().encodeToString(textCriptat);
    }

    public static String decriptare(String textCriptat, SecretKey secretKey) throws Exception {
        Cipher cipher = Cipher.getInstance("AES");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        byte[] textDecriptat = cipher.doFinal(Base64.getDecoder().decode(textCriptat));
        return new String(textDecriptat);
    }


}
