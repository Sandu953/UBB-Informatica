package cs.map.lab7.controller;

import cs.map.lab7.repository.PrietenieDBRepository;
import cs.map.lab7.repository.RequestDBRepository;
import cs.map.lab7.repository.UtilizatorDBRepository;
import cs.map.lab7.service.Service;

public interface BaseController {
    void setUserRepository(UtilizatorDBRepository repoUtilizator);

    void setRepoPrietenie(PrietenieDBRepository repoPrietenie);

    void setRepoRequest(RequestDBRepository repoRequest);

    void setUserService(Service service);
}
