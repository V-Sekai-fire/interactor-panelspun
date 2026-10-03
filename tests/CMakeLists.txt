add_executable(panelspun-tests main.cpp split_tree_test.cpp)
target_link_libraries(panelspun-tests PRIVATE panelspun)

set(PANELSPUN_TEST_CASES
  layout.single-panel-fills-bounds
  layout.three-panels-tile-without-overlap
  layout.tiling-check-rejects-overlap
  handles.hit-test-finds-split-and-misses-panel
  resize.drag-moves-split
  resize.drag-past-minimum-is-clamped
  resize.minimum-holds-when-window-shrinks
  resize.unknown-node-and-leaf-refused
  dock.each-side-places-panel
  dock.refuses-duplicate-missing-target-and-bad-id
  undock.remove-collapses-parent
  undock.removing-last-panel-is-refused
  construct.invalid-first-id-throws
  serialize.round-trip-preserves-layout
  serialize.format-is-line-based
  serialize.malformed-input-rejected
  serialize.deep-nesting-rejected
)
foreach(case IN LISTS PANELSPUN_TEST_CASES)
  add_test(NAME ${case} COMMAND panelspun-tests ${case})
endforeach()

# Every case the binary carries must be registered above, so none is silently skipped.
add_test(NAME registry.every-case-registered
  COMMAND ${CMAKE_COMMAND} -DTESTS=$<TARGET_FILE:panelspun-tests> "-DEXPECTED=${PANELSPUN_TEST_CASES}"
          -P ${CMAKE_CURRENT_SOURCE_DIR}/registry.cmake)
add_test(NAME registry.control-missing-case-fails
  COMMAND ${CMAKE_COMMAND} -DTESTS=$<TARGET_FILE:panelspun-tests> "-DEXPECTED=layout.single-panel-fills-bounds"
          -P ${CMAKE_CURRENT_SOURCE_DIR}/registry.cmake)
set_tests_properties(registry.control-missing-case-fails PROPERTIES WILL_FAIL TRUE)

add_test(NAME all-cases COMMAND panelspun-tests)

foreach(control control.failing-check-fails control.empty-case-fails control.unknown-case-name)
  add_test(NAME ${control} COMMAND panelspun-tests ${control})
  set_tests_properties(${control} PROPERTIES WILL_FAIL TRUE)
endforeach()
