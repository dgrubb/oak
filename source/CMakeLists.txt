target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/A3000.cc
        ${CMAKE_CURRENT_LIST_DIR}/Display.cc
        ${CMAKE_CURRENT_LIST_DIR}/main.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/Device.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/Ioc.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/Memc.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/Ram.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/Rom.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/Arm2.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/Cpsr.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/Register.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/RegisterFile.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/BlockTransfer.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/Branch.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/DataProcessing.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/Multiply.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/Op.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/OpFactory.cc
        ${CMAKE_CURRENT_LIST_DIR}/chipset/arm2/opcodes/SingleTransfer.cc
        ${CMAKE_CURRENT_LIST_DIR}/util/Log.cc
)
