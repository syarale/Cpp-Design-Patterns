set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -g")

find_package(Threads REQUIRED)

add_executable(observer observer.cc)
add_executable(p2p p2p.cc)
add_executable(p2p_observer p2p_observer.cc)

add_executable(p2p_observer_async p2p_observer_async.cc)
target_link_libraries(p2p_observer_async Threads::Threads)