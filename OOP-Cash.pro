#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T21:38:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OOP-Cash
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
        libs\sqlite3.c \
        libs\logger.cpp \
        libs\qcustomplot.cpp \
    util/configuration.cpp \
    util/database_helper.cpp \
    dao/usermanager.cpp \
    dao/currencymanager.cpp \
    dao/categorymanager.cpp \
    dao/accountmanager.cpp \
    model/account.cpp \
    model/category.cpp \
    model/currency.cpp \
    model/user.cpp \
    model/bill.cpp \
    dao/billmanager.cpp \
    dao/query.cpp \
    libs/logger.cpp \
    libs/qcustomplot.cpp \
    libs/sqlite3.c \
    DataVisualization/getdata.cpp \
    DataVisualization/guigetdata.cpp \
    DataVisualization/guiquery.cpp \
    process/processor.cpp \
    process/issamexstrategy.cpp \
    process/issameweek.cpp \
    process/issamemonth.cpp \
    process/issameyear.cpp \
    process/isSameX/issamemonth.cpp \
    process/isSameX/issameweek.cpp \
    process/isSameX/issamexstrategy.cpp \
    process/isSameX/issameyear.cpp \
    process/getY/getystrategy.cpp \
    process/getY/getcategory.cpp \
    process/gui/combobox.cpp \
    process/processorfactory.cpp \
    process/gui/consultant.cpp \
    DataVisualization/mymainwindow.cpp \
    DataVisualization/graphdock.cpp


INCLUDEPATH += include

win32{
    Debug:LIBS += $$PWD\libs\win_x64\sqlpp11-connector-sqlite3_debug.lib
    Release:LIBS += $$PWD\libs\win_x64\sqlpp11-connector-sqlite3_release.lib
}
macx{
    LIBS += $$PWD/libs/darwin_x64/libsqlpp11-connector-sqlite3.a
    debug:DEFINES += _DEBUG
}

HEADERS  += \
    include\qcustomplot.h \
    database/tables.h \
    util/constants.h \
    util/configuration.h \
    util/database_helper.h \
    util/common.h \
    model/user.h \
    dao/usermanager.h \
    dao/itemmanager.h \
    model/currency.h \
    dao/currencymanager.h \
    model/account.h \
    dao/accountmanager.h \
    model/bill.h \
    model/category.h \
    dao/categorymanager.h \
    dao/billmanager.h \
    dao/query.h \
    include/logging/logger.h \
    include/sqlpp11/aggregate_functions/avg.h \
    include/sqlpp11/aggregate_functions/count.h \
    include/sqlpp11/aggregate_functions/max.h \
    include/sqlpp11/aggregate_functions/min.h \
    include/sqlpp11/aggregate_functions/sum.h \
    include/sqlpp11/data_types/boolean/column_operators.h \
    include/sqlpp11/data_types/boolean/data_type.h \
    include/sqlpp11/data_types/boolean/expression_operators.h \
    include/sqlpp11/data_types/boolean/operand.h \
    include/sqlpp11/data_types/boolean/parameter_value.h \
    include/sqlpp11/data_types/boolean/result_field.h \
    include/sqlpp11/data_types/boolean/wrap_operand.h \
    include/sqlpp11/data_types/day_point/column_operators.h \
    include/sqlpp11/data_types/day_point/data_type.h \
    include/sqlpp11/data_types/day_point/expression_operators.h \
    include/sqlpp11/data_types/day_point/operand.h \
    include/sqlpp11/data_types/day_point/parameter_value.h \
    include/sqlpp11/data_types/day_point/result_field.h \
    include/sqlpp11/data_types/day_point/wrap_operand.h \
    include/sqlpp11/data_types/floating_point/column_operators.h \
    include/sqlpp11/data_types/floating_point/data_type.h \
    include/sqlpp11/data_types/floating_point/expression_operators.h \
    include/sqlpp11/data_types/floating_point/operand.h \
    include/sqlpp11/data_types/floating_point/parameter_value.h \
    include/sqlpp11/data_types/floating_point/result_field.h \
    include/sqlpp11/data_types/floating_point/wrap_operand.h \
    include/sqlpp11/data_types/integral/column_operators.h \
    include/sqlpp11/data_types/integral/data_type.h \
    include/sqlpp11/data_types/integral/expression_operators.h \
    include/sqlpp11/data_types/integral/operand.h \
    include/sqlpp11/data_types/integral/parameter_value.h \
    include/sqlpp11/data_types/integral/result_field.h \
    include/sqlpp11/data_types/integral/wrap_operand.h \
    include/sqlpp11/data_types/no_value/column_operators.h \
    include/sqlpp11/data_types/no_value/data_type.h \
    include/sqlpp11/data_types/no_value/expression_operators.h \
    include/sqlpp11/data_types/no_value/operand.h \
    include/sqlpp11/data_types/no_value/parameter_value.h \
    include/sqlpp11/data_types/no_value/result_field.h \
    include/sqlpp11/data_types/no_value/wrap_operand.h \
    include/sqlpp11/data_types/text/column_operators.h \
    include/sqlpp11/data_types/text/concat.h \
    include/sqlpp11/data_types/text/data_type.h \
    include/sqlpp11/data_types/text/expression_operators.h \
    include/sqlpp11/data_types/text/like.h \
    include/sqlpp11/data_types/text/operand.h \
    include/sqlpp11/data_types/text/parameter_value.h \
    include/sqlpp11/data_types/text/result_field.h \
    include/sqlpp11/data_types/text/wrap_operand.h \
    include/sqlpp11/data_types/time_of_day/column_operators.h \
    include/sqlpp11/data_types/time_of_day/data_type.h \
    include/sqlpp11/data_types/time_of_day/expression_operators.h \
    include/sqlpp11/data_types/time_of_day/operand.h \
    include/sqlpp11/data_types/time_of_day/parameter_value.h \
    include/sqlpp11/data_types/time_of_day/result_field.h \
    include/sqlpp11/data_types/time_of_day/wrap_operand.h \
    include/sqlpp11/data_types/time_point/column_operators.h \
    include/sqlpp11/data_types/time_point/data_type.h \
    include/sqlpp11/data_types/time_point/expression_operators.h \
    include/sqlpp11/data_types/time_point/operand.h \
    include/sqlpp11/data_types/time_point/parameter_value.h \
    include/sqlpp11/data_types/time_point/result_field.h \
    include/sqlpp11/data_types/time_point/wrap_operand.h \
    include/sqlpp11/data_types/unsigned_integral/column_operators.h \
    include/sqlpp11/data_types/unsigned_integral/data_type.h \
    include/sqlpp11/data_types/unsigned_integral/expression_operators.h \
    include/sqlpp11/data_types/unsigned_integral/operand.h \
    include/sqlpp11/data_types/unsigned_integral/parameter_value.h \
    include/sqlpp11/data_types/unsigned_integral/result_field.h \
    include/sqlpp11/data_types/unsigned_integral/wrap_operand.h \
    include/sqlpp11/data_types/boolean.h \
    include/sqlpp11/data_types/column_operators.h \
    include/sqlpp11/data_types/day_point.h \
    include/sqlpp11/data_types/floating_point.h \
    include/sqlpp11/data_types/integral.h \
    include/sqlpp11/data_types/no_value.h \
    include/sqlpp11/data_types/parameter_value.h \
    include/sqlpp11/data_types/parameter_value_base.h \
    include/sqlpp11/data_types/text.h \
    include/sqlpp11/data_types/time_of_day.h \
    include/sqlpp11/data_types/time_point.h \
    include/sqlpp11/data_types/unsigned_integral.h \
    include/sqlpp11/detail/copy_tuple_args.h \
    include/sqlpp11/detail/enable_if.h \
    include/sqlpp11/detail/field_index_sequence.h \
    include/sqlpp11/detail/get_first.h \
    include/sqlpp11/detail/get_last.h \
    include/sqlpp11/detail/index_sequence.h \
    include/sqlpp11/detail/pick_arg.h \
    include/sqlpp11/detail/sum.h \
    include/sqlpp11/detail/type_set.h \
    include/sqlpp11/detail/type_vector.h \
    include/sqlpp11/detail/void.h \
    include/sqlpp11/ppgen/colops/auto_increment.h \
    include/sqlpp11/ppgen/colops/blob.h \
    include/sqlpp11/ppgen/colops/bool.h \
    include/sqlpp11/ppgen/colops/comment.h \
    include/sqlpp11/ppgen/colops/datetime.h \
    include/sqlpp11/ppgen/colops/default.h \
    include/sqlpp11/ppgen/colops/floating_point.h \
    include/sqlpp11/ppgen/colops/foreign_key.h \
    include/sqlpp11/ppgen/colops/index.h \
    include/sqlpp11/ppgen/colops/integer.h \
    include/sqlpp11/ppgen/colops/not_null.h \
    include/sqlpp11/ppgen/colops/null.h \
    include/sqlpp11/ppgen/colops/primary_key.h \
    include/sqlpp11/ppgen/colops/text.h \
    include/sqlpp11/ppgen/colops/timestamp.h \
    include/sqlpp11/ppgen/colops/unique_index.h \
    include/sqlpp11/ppgen/colops/varchar.h \
    include/sqlpp11/ppgen/tblops/character_set.h \
    include/sqlpp11/ppgen/tblops/comment.h \
    include/sqlpp11/ppgen/tblops/default.h \
    include/sqlpp11/ppgen/tblops/engine.h \
    include/sqlpp11/ppgen/tools/tuple_pop_front.h \
    include/sqlpp11/ppgen/tools/wrap_seq.h \
    include/sqlpp11/sqlite3/bind_result.h \
    include/sqlpp11/sqlite3/connection.h \
    include/sqlpp11/sqlite3/connection_config.h \
    include/sqlpp11/sqlite3/insert_or.h \
    include/sqlpp11/sqlite3/prepared_statement.h \
    include/sqlpp11/sqlite3/serializer.h \
    include/sqlpp11/sqlite3/sqlite3.h \
    include/sqlpp11/aggregate_functions.h \
    include/sqlpp11/alias.h \
    include/sqlpp11/alias_operators.h \
    include/sqlpp11/alias_provider.h \
    include/sqlpp11/all_of.h \
    include/sqlpp11/any.h \
    include/sqlpp11/assignment.h \
    include/sqlpp11/auto_alias.h \
    include/sqlpp11/bad_expression.h \
    include/sqlpp11/basic_expression_operators.h \
    include/sqlpp11/boolean_expression.h \
    include/sqlpp11/case.h \
    include/sqlpp11/char_sequence.h \
    include/sqlpp11/chrono.h \
    include/sqlpp11/column.h \
    include/sqlpp11/column_fwd.h \
    include/sqlpp11/column_types.h \
    include/sqlpp11/connection.h \
    include/sqlpp11/connection_pool.h \
    include/sqlpp11/consistent.h \
    include/sqlpp11/cte.h \
    include/sqlpp11/custom_query.h \
    include/sqlpp11/data_types.h \
    include/sqlpp11/default_value.h \
    include/sqlpp11/dynamic_join.h \
    include/sqlpp11/dynamic_pre_join.h \
    include/sqlpp11/dynamic_select_column_list.h \
    include/sqlpp11/eval.h \
    include/sqlpp11/exception.h \
    include/sqlpp11/exists.h \
    include/sqlpp11/expression.h \
    include/sqlpp11/expression_fwd.h \
    include/sqlpp11/expression_operators.h \
    include/sqlpp11/expression_return_types.h \
    include/sqlpp11/field_spec.h \
    include/sqlpp11/for_update.h \
    include/sqlpp11/from.h \
    include/sqlpp11/functions.h \
    include/sqlpp11/group_by.h \
    include/sqlpp11/having.h \
    include/sqlpp11/hidden.h \
    include/sqlpp11/in.h \
    include/sqlpp11/in_fwd.h \
    include/sqlpp11/inconsistent.h \
    include/sqlpp11/insert.h \
    include/sqlpp11/insert_value.h \
    include/sqlpp11/insert_value_list.h \
    include/sqlpp11/interpret.h \
    include/sqlpp11/interpret_tuple.h \
    include/sqlpp11/interpretable.h \
    include/sqlpp11/interpretable_list.h \
    include/sqlpp11/interpreter.h \
    include/sqlpp11/into.h \
    include/sqlpp11/is_not_null.h \
    include/sqlpp11/is_null.h \
    include/sqlpp11/is_null_fwd.h \
    include/sqlpp11/join.h \
    include/sqlpp11/join_types.h \
    include/sqlpp11/limit.h \
    include/sqlpp11/logic.h \
    include/sqlpp11/multi_column.h \
    include/sqlpp11/named_interpretable.h \
    include/sqlpp11/no_data.h \
    include/sqlpp11/no_name.h \
    include/sqlpp11/noop.h \
    include/sqlpp11/noop_fwd.h \
    include/sqlpp11/not_in.h \
    include/sqlpp11/null.h \
    include/sqlpp11/offset.h \
    include/sqlpp11/on.h \
    include/sqlpp11/operand_check.h \
    include/sqlpp11/order_by.h \
    include/sqlpp11/parameter.h \
    include/sqlpp11/parameter_list.h \
    include/sqlpp11/policy_update.h \
    include/sqlpp11/pool_connection.h \
    include/sqlpp11/portable_static_assert.h \
    include/sqlpp11/ppgen.h \
    include/sqlpp11/pre_join.h \
    include/sqlpp11/prepared_execute.h \
    include/sqlpp11/prepared_insert.h \
    include/sqlpp11/prepared_remove.h \
    include/sqlpp11/prepared_select.h \
    include/sqlpp11/prepared_update.h \
    include/sqlpp11/remove.h \
    include/sqlpp11/result.h \
    include/sqlpp11/result_field.h \
    include/sqlpp11/result_field_base.h \
    include/sqlpp11/result_row.h \
    include/sqlpp11/result_row_fwd.h \
    include/sqlpp11/rhs_wrap.h \
    include/sqlpp11/schema.h \
    include/sqlpp11/schema_qualified_table.h \
    include/sqlpp11/select.h \
    include/sqlpp11/select_column_list.h \
    include/sqlpp11/select_flag_list.h \
    include/sqlpp11/select_flags.h \
    include/sqlpp11/select_pseudo_table.h \
    include/sqlpp11/serialize.h \
    include/sqlpp11/serializer.h \
    include/sqlpp11/serializer_context.h \
    include/sqlpp11/simple_column.h \
    include/sqlpp11/single_table.h \
    include/sqlpp11/some.h \
    include/sqlpp11/sort_order.h \
    include/sqlpp11/sqlpp11.h \
    include/sqlpp11/statement.h \
    include/sqlpp11/statement_fwd.h \
    include/sqlpp11/table.h \
    include/sqlpp11/table_alias.h \
    include/sqlpp11/table_ref.h \
    include/sqlpp11/transaction.h \
    include/sqlpp11/tvin.h \
    include/sqlpp11/type_traits.h \
    include/sqlpp11/unconditional.h \
    include/sqlpp11/union.h \
    include/sqlpp11/union_data.h \
    include/sqlpp11/union_flags.h \
    include/sqlpp11/update.h \
    include/sqlpp11/update_list.h \
    include/sqlpp11/using.h \
    include/sqlpp11/value.h \
    include/sqlpp11/value_or_null.h \
    include/sqlpp11/value_type.h \
    include/sqlpp11/value_type_fwd.h \
    include/sqlpp11/verbatim.h \
    include/sqlpp11/verbatim_table.h \
    include/sqlpp11/where.h \
    include/sqlpp11/with.h \
    include/sqlpp11/without_table_check.h \
    include/sqlpp11/wrap_operand.h \
    include/sqlpp11/wrong.h \
    include/date.h \
    include/qcustomplot.h \
    include/sqlite3.h \
    DataVisualization/guigetdata.h \
    DataVisualization/guiquery.h \
    process/processor.h \
    process/issamexstrategy.h \
    process/issameweek.h \
    process/issamemonth.h \
    process/issameyear.h \
    process/isSameX/issamemonth.h \
    process/isSameX/issameweek.h \
    process/isSameX/issamexstrategy.h \
    process/isSameX/issameyear.h \
    process/getY/getystrategy.h \
    process/getY/getfromaccount.h \
    process/getY/gettoaccount.h \
    process/getY/getcategory.h \
    process/gui/combobox.h \
    process/processorfactory.h \
    process/gui/consultant.h \
    DataVisualization/mymainwindow.h \
    DataVisualization/graphdock.h

FORMS    += \
    mainwindow.ui \
    DataVisualization/mymainwindow.ui \
    DataVisualization/graphdock.ui
