package cs.map.lab7.service;


import cs.map.lab7.domain.*;
import cs.map.lab7.repository.*;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service {
    private final UtilizatorDBRepository repoUtilizatori;
    private final PrietenieDBRepository repoPrietenii;
    private final RequestDBRepository repoRequest;
    private final MessageDBRepository repoMesaj;


    /**
     * constructor
     */
    public Service(UtilizatorDBRepository repoUtilizatori,
                   PrietenieDBRepository repoPrietenii,
                   RequestDBRepository repoRequest, MessageDBRepository repoMesaj) {
        this.repoUtilizatori = repoUtilizatori;
        this.repoPrietenii = repoPrietenii;
        this.repoRequest = repoRequest;
        this.repoMesaj = repoMesaj;
    }

    /**
     * addd an user
     *
     * @param idUtilizator long
     * @param firstName    String
     * @param lastName     String
     * @throws Error if id invalid
     */
    public void addUtilizator(long idUtilizator, String firstName, String lastName) throws Error {
        Utilizator utilizator = new Utilizator(firstName, lastName);
        utilizator.setId(idUtilizator);
        utilizator.setUsername();
        utilizator.setPassword();
        Optional<Utilizator> ok = repoUtilizatori.save(utilizator);
        if (ok.isPresent()) throw new Error("Id invalid");
    }

    public boolean existaUser(String usename, String password){
        return repoUtilizatori.findOneUserName(usename,password);
    }

    public void addMessage(long id_from, List<Long> id_to, String message) throws Exception {
        List<Utilizator> utilizatori = new ArrayList<>();
        if (repoUtilizatori.findOne(id_from).isEmpty()) throw new Exception("Nu exista utilizatorul");
        id_to.forEach(id -> repoUtilizatori.findOne(id).ifPresent(utilizatori::add));
        Message m = new Message(repoUtilizatori.findOne(id_from).get(), utilizatori, message, LocalDateTime.now());
        int l = 0;
        for (Message me : repoMesaj.findAll()) {
            l += 1;
        }
        m.setId((long) l + 1);
        for (Message me : repoMesaj.findAll()) {
            if (id_to.contains(me.getFrom().getId()) &&
                    me.getTo().contains(repoUtilizatori.findOne(id_from).get())
                    && me.getReply() == null) {
                me.setReply(m);
                repoMesaj.update(me);
            }
        }
        repoMesaj.save(m);
        System.out.println(m);
    }

    public List<Message> conversation(long id1, long id2) {
        List<Message> conv = StreamSupport.stream(repoMesaj.findAll().spliterator(), false)
                .filter(msg ->
                        (msg.getTo().contains(repoUtilizatori.findOne(id2).get()) &&
                                msg.getFrom().getId() == id1) ||
                                (msg.getTo().contains(repoUtilizatori.findOne(id1).get()) &&
                                        msg.getFrom().getId() == id2))
                .sorted(Comparator.comparing(Message::getData))
                .collect(Collectors.toList());
        return conv;
    }

    public void addRequest(long idfrom, long idto) throws Exception {
        if (repoUtilizatori.findOne(idfrom).isEmpty() || repoUtilizatori.findOne(idto).isEmpty())
            throw new Exception("Nu exista utilizatorul");
        FriendRequest request = new FriendRequest(idfrom, idto, repoUtilizatori.findOne(idfrom).get().getUsername());
        Optional<FriendRequest> ok = repoRequest.save(request);
        if (ok.isPresent()) throw new Error("Id invalid");
    }

    public void updateRequest(FriendRequest request, Status status) {
        request.setStatus(status);
        repoRequest.update(request);
    }


    public void updateUtilizator(long idUtilizator, String firstName, String lastName) throws Error {
        Utilizator utilizator = new Utilizator(firstName, lastName);
        utilizator.setId(idUtilizator);
        utilizator.setPassword();
        utilizator.setUsername();
        if (repoUtilizatori.findOne(idUtilizator).isEmpty()) throw new Error("Nu exista utilizatorul!");
        repoUtilizatori.update(utilizator);
    }

    /**
     * delete  user and its Friendships
     *
     * @param idUtilizator long
     * @throws Error if repo does not have the user
     */
    public void deleteUtilizator(long idUtilizator) throws Error {

        Optional<Utilizator> utilizator = repoUtilizatori.delete(idUtilizator);
        if (utilizator.isEmpty()) throw new Error("Utilizator inexistent");
        Iterable<Prietenie> prietenii = repoPrietenii.findAll();
        List<Prietenie> toDelete = new ArrayList<>();
        prietenii.forEach(prietenie -> {
            if (prietenie.memberOf(idUtilizator)) {
                toDelete.add(prietenie);
            }
        });
        toDelete.forEach(prietenie -> repoPrietenii.delete(prietenie.getId()));

    }

    /**
     * create a friendship betweeen user1 and user2
     *
     * @param idUtilizator1 long
     * @param idUtilizator2 long
     * @throws Error -> priteenie existenta
     *               -> utilizator inexistent
     */
    public void addFriendship(long idUtilizator1, long idUtilizator2, LocalDate data) throws Error {

        if (repoUtilizatori.findOne(idUtilizator1).isPresent() && repoUtilizatori.findOne(idUtilizator2).isPresent()) {
            Prietenie prietenie = new Prietenie(data, idUtilizator1, idUtilizator2);
            if (repoPrietenii.findOne(new Tuple<>(idUtilizator1, idUtilizator2)).isEmpty()) {
                prietenie.setId(new Tuple<>(idUtilizator1, idUtilizator2));
            } else throw new Error(("Prietenie existenta " + idUtilizator1 + idUtilizator2));
            repoPrietenii.save(prietenie);
        } else throw new Error("Utilizator inexistent");
    }

    /**
     * delete a friendship
     *
     * @param idUtilizator1 long
     * @param idUtilizator2 long
     * @throws Error ->(prietenie inexistent)
     */
    public void deleteFriendship(long idUtilizator1, long idUtilizator2) throws Error {

        if (repoPrietenii.delete(new Tuple<>(idUtilizator1, idUtilizator2)).isEmpty() && repoPrietenii.delete(
                new Tuple<>(idUtilizator2, idUtilizator1)).isEmpty())
            throw new Error("Prietenie inexistenta");

    }

    public void updateAllUsers() {
        for (Utilizator u : repoUtilizatori.findAll()) {
            repoUtilizatori.update(u);
        }
    }

    /**
     * return all the users
     *
     * @return Iterable Utilizator
     */
    public Iterable<Utilizator> getAllUtilizatori() {
        return repoUtilizatori.findAll();
    }

    public Page<Utilizator> findAllUsers(Pageable pageable) {
        return repoUtilizatori.findAll(pageable);
    }

    public Optional<Utilizator> findAfterUserName(String username) {
        Iterable<Utilizator> users = repoUtilizatori.findAll();
        for (Utilizator u : users) {
            if (Objects.equals(u.getUsername(), username)) {
                return Optional.of(u);
            }
        }
        return Optional.empty();
    }

    public Iterable<Utilizator> getUserFriendsIterable(String username) {
        Iterable<Prietenie> prietenii = repoPrietenii.findAll();
        ArrayList<Utilizator> userSet = new ArrayList<>();
        for (Prietenie p : prietenii) {
            if (Objects.equals(repoUtilizatori.findOne(p.getId().getLeft()).get().getUsername(), username)) {
                userSet.add(repoUtilizatori.findOne(p.getId().getRight()).get());
            } else if (Objects.equals(repoUtilizatori.findOne(p.getId().getRight()).get().getUsername(), username)) {
                userSet.add(repoUtilizatori.findOne(p.getId().getLeft()).get());
            }
        }
        return userSet;
    }

    public Iterable<FriendRequest> getUsersFriendRequest(String username) {
        Iterable<FriendRequest> requests = repoRequest.findAll();
        ArrayList<FriendRequest> requestSet = new ArrayList<>();
        System.out.println(username);
        for (FriendRequest r : requests) {
            //System.out.println(r.getIdto());
            if (findAfterUserName(username).isPresent() && r.getIdto() == findAfterUserName(username).get().getId()) {
                requestSet.add(r);
            }
        }
        return requestSet;
    }


    public Iterable<FriendRequest> getAllRequest() {
        return repoRequest.findAll();
    }

    public Page<FriendRequest> findAllRequest(Pageable pageable) {
        return repoRequest.findAll(pageable);
    }

    /**
     * return the community which the user take part
     *
     * @param idUtilizator ;ong
     * @return List<Utilizator>
     */
    private List<Optional<Utilizator>> groupOfFriends(long idUtilizator) {

        Iterable<Prietenie> prieteni = repoPrietenii.findAll();
        List<Optional<Utilizator>> prieteniUtilizator = new ArrayList<>();
        Optional<Utilizator> utilizator = repoUtilizatori.findOne(idUtilizator);
        prieteniUtilizator.add(utilizator);

        for (Prietenie prietenie : prieteni) {
            if (prietenie.prietenComun(idUtilizator) != -1)
                prieteniUtilizator.add(repoUtilizatori.findOne(prietenie.prietenComun(idUtilizator)));
        }

        prieteni.forEach(prietenie -> {
            if (prietenie.prietenComun(idUtilizator) != -1)
                prieteniUtilizator.add(repoUtilizatori.findOne(prietenie.prietenComun(idUtilizator)));
        });

        return prieteniUtilizator;

    }

    /**
     * DFS on the list of users based on friendships
     *
     * @param utilizator
     * @param set
     * @return
     */
    private List<Optional<Utilizator>> DFS(Optional<Utilizator> utilizator, Set<Optional<Utilizator>> set) {
        List<Optional<Utilizator>> lista = new ArrayList<>();
        set.add(utilizator);
        lista.add(utilizator);

        groupOfFriends(utilizator.get().getId()).stream().filter(
                u -> !set.contains(u)).map(u -> DFS(u, set)).forEach(lista::addAll);
        return lista;

    }

    /**
     * @return the number of communities (number of connectected components)
     */
    public int numberOfCommunities() {
        Iterable<Utilizator> utilizatori = repoUtilizatori.findAll();
        Set<Optional<Utilizator>> set = new HashSet<>();
        AtomicInteger contor = new AtomicInteger();
        utilizatori.forEach(utilizator -> {
            if (!set.contains(utilizator)) {
                set.add(Optional.of(utilizator));
                contor.getAndIncrement();
                DFS(Optional.of(utilizator), set);
            }
        });
        return contor.get();
    }

    /**
     * return a list with all the Communities and their users
     *
     * @return List<List < Utilizator>>
     */
    public List<List<Optional<Utilizator>>> getAllCommunities() {
        List<List<Optional<Utilizator>>> communities = new ArrayList<>();
        Iterable<Utilizator> utilizatori = repoUtilizatori.findAll();
        HashSet<Optional<Utilizator>> set = new HashSet<>();

        utilizatori.forEach(utilizator -> {
            if (!set.contains(utilizator)) {
                communities.add(DFS(Optional.of(utilizator), set));
            }
        });

        utilizatori.forEach(utilizator -> {
            if (!set.contains(utilizator)) {
                communities.add(DFS(Optional.of(utilizator), set));
            }
        });

        return communities;
    }

    /**
     * @return theBiggestCommunity
     */
    public List<Optional<Utilizator>> theBiggestCommunity() {
        List<List<Optional<Utilizator>>> communities = getAllCommunities();
        AtomicReference<List<Optional<Utilizator>>> theBiggestCommunity =
                new AtomicReference<>(new ArrayList<>());
        AtomicInteger size = new AtomicInteger();
        communities.forEach(comunity -> {
            System.out.println("Comunitatea ");
            int lungime = longestPath(comunity);
            System.out.println("Comunitatea " + lungime);
            if (lungime > size.get()) {
                size.set(lungime);
                theBiggestCommunity.set(comunity);
            }
        });
        System.out.println(size.get());
        return theBiggestCommunity.get();
    }

    private int longestPath(List<Optional<Utilizator>> comunity) {
        int max = 0;
        for (Optional<Utilizator> utilizator : comunity) {
            int lungime = longestPathFromSource(utilizator);
            if (lungime > max) max = lungime;
        }
        return max;
    }

    private int longestPathFromSource(Optional<Utilizator> utilizator) {
        Set<Optional<Utilizator>> set = new HashSet<>();
        return lee(utilizator, set);
    }

    private int lee(Optional<Utilizator> source, Set<Optional<Utilizator>> set) {
        AtomicInteger max = new AtomicInteger(-1);
        groupOfFriends(source.get().getId()).forEach(f -> {
            if (!set.contains(f) && !f.equals(source)) {
                set.add(f);
                int l = lee(f, set);
                if (l > max.get()) {
                    max.set(l);
                }
                set.remove(f);
            }
        });

        return max.get() + 1;
    }

    /**
     * return all Friendships
     *
     * @return Iterable Prietenie
     */
    public Iterable<Prietenie> getAllFriendships() {
        return repoPrietenii.findAll();
    }

    public List<Tuple<Utilizator, Integer>> getUsersFriends(int n) {
        Iterable<Utilizator> lista = getAllUtilizatori();
        Iterable<Prietenie> prietenii = getAllFriendships();

        Map<Utilizator, Integer> userCountMap = StreamSupport.stream(lista.spliterator(), false)
                .collect(Collectors.toMap(utilizator -> utilizator,
                        utilizator -> Math.toIntExact(StreamSupport.stream(prietenii.spliterator(), false)
                                .filter(prietenie -> prietenie.prietenComun(utilizator.getId()) != -1)
                                .count())
                ));

        return userCountMap.entrySet().stream()
                .filter(entry -> entry.getValue() >= n)
                .map(entry -> new Tuple<>(entry.getKey(), entry.getValue()))
                .collect(Collectors.toList());
    }


    public List<Tuple<Optional<Utilizator>, Prietenie>> getFriendshipsFromMonth(long id, int month) {
        Iterable<Prietenie> prietenii = getAllFriendships();
        List<Tuple<Optional<Utilizator>, Prietenie>> ret = new ArrayList<>();
        prietenii.forEach(p -> {
            if (p.prietenComun(id) != -1 && p.getDate().getMonthValue() == month) {
                Tuple<Optional<Utilizator>, Prietenie> tu = new Tuple<>(repoUtilizatori.findOne(p.prietenComun(id)), p);
                ret.add(tu);
            }
        });
        return ret;
    }


    public List<Utilizator> getUsersString(String s) {
        return repoUtilizatori.getUsersString(s);
    }
}
