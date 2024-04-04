package cs.map.lab7.repository;


import cs.map.lab7.domain.FriendRequest;
import cs.map.lab7.domain.Status;
import cs.map.lab7.domain.Tuple;
import cs.map.lab7.domain.Utilizator;

import javax.crypto.SecretKey;
import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class RequestDBRepository implements PagingRepository<Tuple<Long, Long>, FriendRequest> {

    private final String Url;
    private final String User;
    private final String Password;

    private UtilizatorDBRepository repoUser;

    public RequestDBRepository(String url, String user, String password, SecretKey secretKey) {
        this.Url = url;
        this.Password = password;
        this.User = user;
        this.repoUser = new UtilizatorDBRepository(url, user, password, secretKey);
    }

    @Override
    public Optional<FriendRequest> findOne(Tuple<Long, Long> longLongTuple) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement1 = connection.prepareStatement(
                     "select * from friendrequest where idfrom=? AND idto =?");
             PreparedStatement statement2 = connection.prepareStatement(
                     "select * from friendrequest where idfrom=? AND idto =?")) {

            statement1.setInt(1, Math.toIntExact(longLongTuple.getLeft()));
            statement1.setInt(2, Math.toIntExact(longLongTuple.getRight()));
            ResultSet resultSet = statement1.executeQuery();
            if (!resultSet.next()) {
                statement2.setInt(1, Math.toIntExact(longLongTuple.getRight()));
                statement2.setInt(2, Math.toIntExact(longLongTuple.getLeft()));
                ResultSet resultSet1 = statement2.executeQuery();
                if (resultSet1.next()) {
                    var dt = resultSet1.getDate("requestfrom").toLocalDate();
                    Status st = Status.valueOf(resultSet1.getString("status"));
                    Optional<Utilizator> user = repoUser.findOne(longLongTuple.getLeft());
                    FriendRequest r = new FriendRequest(longLongTuple.getLeft(), longLongTuple.getRight(),
                            dt, st, user.get().getUsername());
                    return Optional.ofNullable(r);
                }
            } else {
                var dt = resultSet.getDate("requestfrom").toLocalDate();
                Status st = Status.valueOf(resultSet.getString("status"));
                Optional<Utilizator> user = repoUser.findOne(longLongTuple.getLeft());
                FriendRequest r = new FriendRequest(longLongTuple.getLeft(), longLongTuple.getRight(),
                        dt, st, user.get().getUsername());
                return Optional.ofNullable(r);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return Optional.empty();
    }

    @Override
    public Iterable<FriendRequest> findAll() {
        ArrayList<FriendRequest> requestSet = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "select * from friendrequest");
        ) {
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next()) {
                Long idfrom = resultSet.getLong("idfrom");
                Long idto = resultSet.getLong("idto");
                var dt = resultSet.getDate("requestfrom").toLocalDate();
                Status st = Status.valueOf(resultSet.getString("status"));
                Optional<Utilizator> user = repoUser.findOne(idfrom);
                if (user.isPresent()) {
                    FriendRequest request = new FriendRequest(idfrom, idto, dt, st, user.get().getUsername());
                    requestSet.add(request);
                }
            }
            return requestSet;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<FriendRequest> save(FriendRequest entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "insert into friendrequest(idfrom,idto,requestfrom,status,username) values (?,?,?,?,?)")
        ) {
            var idfrom = entity.getId().getLeft();
            var idto = entity.getId().getRight();
            statement.setInt(1, Math.toIntExact(idfrom));
            statement.setInt(2, Math.toIntExact(idto));
            var dt = LocalDate.of(
                    entity.getData().getYear(), entity.getData().getMonthValue(),
                    entity.getData().getDayOfMonth());
            statement.setDate(3, Date.valueOf(dt));
            Status st = entity.getStatus();
            statement.setString(4, st.toString());
            Optional<Utilizator> user = repoUser.findOne(idfrom);
            statement.setString(5, user.get().getUsername());
            statement.executeUpdate();
            return Optional.empty();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Optional<FriendRequest> delete(Tuple<Long, Long> longLongTuple) {
        try (Connection connection2 = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement2 = connection2.prepareStatement(
                     "DELETE FROM friendrequest WHERE idfrom = ? and idto = ?");) {
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
    public Optional<FriendRequest> update(FriendRequest entity) {
        try (Connection connection = DriverManager.getConnection(Url, User, Password);
             PreparedStatement statement = connection.prepareStatement(
                     "update friendrequest set status = ? where idfrom = ? and idto = ?");) {
            statement.setString(1, entity.getStatus().toString());
            statement.setInt(2, Math.toIntExact(entity.getIdfrom()));
            statement.setInt(3, Math.toIntExact(entity.getIdto()));
            statement.executeUpdate();
            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Page<FriendRequest> findAll(Pageable pageable) {
        List<FriendRequest> requestSet = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(this.Url, this.User, this.Password);
             PreparedStatement pagePreparedStatement = connection.prepareStatement("SELECT * FROM friendrequest " +
                     "LIMIT ? OFFSET ?");

             PreparedStatement countPreparedStatement = connection.prepareStatement
                     ("SELECT COUNT(*) AS count FROM friendrequest ");

        ) {
            pagePreparedStatement.setInt(1, pageable.getPageSize());
            pagePreparedStatement.setInt(2, pageable.getPageSize() * pageable.getPageNumber());
            try (ResultSet pageResultSet = pagePreparedStatement.executeQuery();
                 ResultSet countResultSet = countPreparedStatement.executeQuery();) {
                while (pageResultSet.next()) {
                    Long idfrom = pageResultSet.getLong("idfrom");
                    Long idto = pageResultSet.getLong("idto");
                    var dt = pageResultSet.getDate("requestfrom").toLocalDate();
                    Status st = Status.valueOf(pageResultSet.getString("status"));
                    Optional<Utilizator> user = repoUser.findOne(idfrom);
                    FriendRequest request = new FriendRequest(idfrom, idto, dt, st, user.get().getUsername());
                    requestSet.add(request);
                }
                int totalCount = 0;
                if (countResultSet.next()) {
                    totalCount = countResultSet.getInt("count");
                }

                return new Page<>(requestSet, totalCount);

            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}

