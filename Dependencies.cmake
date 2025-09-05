include(cmake/CPM.cmake)

function(project_setup_dependencies out_deps)
  # For each dependency, see if it's already been
  # provided to use by parent projects
  # and add to the dependency list
  #
  # if(NOT TARGET ${dependency_name})
  #	cpmaddpackage(...)
  # endif()
  # list(APPEND local_deps ${dependency_name})

  set(local_deps "")

  if(NOT TARGET fmt::fmt)
    cpmaddpackage("gh:fmtlib/fmt#11.1.4")
  endif()
  list(APPEND local_deps fmt::fmt)

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      VERSION
      1.15.3
      GITHUB_REPOSITORY
      "gabime/spdlog"
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON")
  endif()
  list(APPEND local_deps spdlog::spdlog)

  # Export the list to the called
  set(${out_deps} ${local_deps} PARENT_SCOPE)

endfunction()
