package cs.map.lab7.domain;

import java.time.LocalDate;
import java.util.Objects;

public class FriendRequest extends cs.map.lab7.domain.Entity<Tuple<Long, Long>> {
    private final long idfrom;
    private final long idto;
    private LocalDate data;
    private Status status;
    private String username;


    public FriendRequest(long idfrom, long idto, LocalDate data, Status s, String username) {
        this.idfrom = idfrom;
        this.idto = idto;
        this.data = data;
        this.status = s;
        this.username = username;
        this.setId(new Tuple(idfrom, idto));
    }

    public FriendRequest(long idfrom, long idto, String username) {
        this.idfrom = idfrom;
        this.idto = idto;
        this.data = LocalDate.now();
        this.status = Status.pending;
        this.username = username;
        this.setId(new Tuple(idfrom, idto));
    }

    public long getIdfrom() {
        return idfrom;
    }

    public long getIdto() {
        return idto;
    }

    public LocalDate getData() {
        return data;
    }

    public void setData(LocalDate data) {
        this.data = data;
    }

    public void setUsername(String username1) {
        this.username = username1;
    }

    public String getUsername() {
        return username;
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        FriendRequest that = (FriendRequest) o;
        return idfrom == that.idfrom && idto == that.idto && Objects.equals(data, that.data) && Objects.equals(status, that.status);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), idfrom, idto, data, status);
    }

    @Override
    public String toString() {
        return "FriendRequest{" +
                "idfrom=" + idfrom +
                ", idto=" + idto +
                ", data=" + data +
                ", status='" + status + '\'' +
                ", id=" + id +
                '}';
    }
}
