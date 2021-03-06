require 'test_helper'

class ConfigControllerTest < ActionController::TestCase
  include AuthenticatedTestHelper

  def test_without_login
    get(:index)
    assert_redirected_to(new_session_path)
  end

  def test_sub_menu_before_connection_setup
    login_as(:aaron)

    default_connection = Config::Connection.default
    default_connection.spec = nil
    default_connection.save(false)
    get(:index)
    assert_select("div.sub-menu a[href=#{config_milters_path}]", 0)
    assert_select("div.sub-menu a[href=#{config_applicable_conditions_path}]", 0)
  end

  def test_sub_menu_after_connection_setup
    login_as(:aaron)

    get(:index)
    assert_select("div.sub-menu a[href=#{config_milters_path}]")
    assert_select("div.sub-menu a[href=#{config_applicable_conditions_path}]")
  end
end
