#include "ks_prm_module.h"
#include "ks_framework.h"
#include "ks_fs_module.h"
#include "ks_sch_module.h"
#include "ks_wrk_module.h"
#include "ks_worker_manager.h"
#include "ks_scheduler.h"
#include "ks_parameter_database.h"

namespace kronos {

    ErrorOr<void> ParamsModule::Init() const {
        TRY(ks_error_component_create, Framework::CreateSingletonComponent<ParameterDatabase>(), void);

        Scheduler::ScheduleEvent(5000, ks_event_save_param, &ParameterDatabase::GetInstance());
        WorkerManager::RegisterComponent(ks_worker_main, &ParameterDatabase::GetInstance());

        return {};
    }

    List <TypeInfo> ParamsModule::GetModuleDependencies() const {
        return Module::DependsOn<SchedModule, FsModule, WorkerModule>();
    }

    List <TypeInfo> ParamsModule::GetExportedComponents() const {
        return Module::ExportComponents<ParameterDatabase>();
    }

}