TESTS = test/run-test.sh

admindir = $(pkgdatadir)/admin

# find . -type f -perm +111 | sed -e 's,^\./,	,' | sort
nobase_dist_admin_SCRIPTS =			\
	public/dispatch.cgi			\
	public/dispatch.fcgi			\
	public/dispatch.rb			\
	script/about				\
	script/console				\
	script/dbconsole			\
	script/destroy				\
	script/generate				\
	script/performance/benchmarker		\
	script/performance/profiler		\
	script/performance/request		\
	script/plugin				\
	script/process/inspector		\
	script/process/reaper			\
	script/process/spawner			\
	script/runner				\
	script/server				\
	test/run-test.sh

# find . -name '.svn' -prune -o -path './log' -prune -o -path './config/secret' -prune -o -not -name '*.sqlite3' -not -name 'Makefile*' -not -name 'schema.rb' -type f -not -perm +111 -print | sed -e 's,^\./,	,' | sort
nobase_dist_admin_DATA =							\
	.autotest								\
	README									\
	Rakefile								\
	TODO									\
	app/controllers/application_controller.rb				\
	app/controllers/config/applicable_conditions_controller.rb		\
	app/controllers/config/connections_controller.rb			\
	app/controllers/config/milters_controller.rb				\
	app/controllers/config_controller.rb					\
	app/controllers/control_controller.rb					\
	app/controllers/sessions_controller.rb					\
	app/controllers/users_controller.rb					\
	app/controllers/welcome_controller.rb					\
	app/helpers/application_helper.rb					\
	app/helpers/config/applicable_conditions_helper.rb			\
	app/helpers/config/connections_helper.rb				\
	app/helpers/config/milters_helper.rb					\
	app/helpers/config_helper.rb						\
	app/helpers/control_helper.rb						\
	app/helpers/sessions_helper.rb						\
	app/helpers/users_helper.rb						\
	app/helpers/welcome_helper.rb						\
	app/models/config/applicable_condition.rb				\
	app/models/config/connection.rb						\
	app/models/config/milter.rb						\
	app/models/config/restriction.rb					\
	app/models/configuration.rb						\
	app/models/user.rb							\
	app/views/config/applicable_conditions/index.html.erb			\
	app/views/config/applicable_conditions/show.html.erb			\
	app/views/config/connections/edit.html.erb				\
	app/views/config/connections/show.html.erb				\
	app/views/config/index.html.erb						\
	app/views/config/milters/edit.html.erb					\
	app/views/config/milters/index.html.erb					\
	app/views/config/milters/new.html.erb					\
	app/views/config/milters/show.html.erb					\
	app/views/control/index.html.erb					\
	app/views/layouts/_footer.html.erb					\
	app/views/layouts/_header.html.erb					\
	app/views/layouts/application.html.erb					\
	app/views/rescues/404.html.erb						\
	app/views/rescues/500.html.erb						\
	app/views/sessions/new.html.erb						\
	app/views/users/new.html.erb						\
	app/views/welcome/index.html.erb					\
	config/boot.rb								\
	config/database.yml							\
	config/environment.rb							\
	config/environments/development.rb					\
	config/environments/production.rb					\
	config/environments/test.rb						\
	config/initializers/inflections.rb					\
	config/initializers/mime_types.rb					\
	config/initializers/new_rails_defaults.rb				\
	config/initializers/site_keys.rb					\
	config/locales/en.yml							\
	config/locales/ja.yml							\
	config/locales/rails/ja.yml						\
	config/routes.rb							\
	db/.gitignore								\
	db/migrate/20081125042659_create_milters.rb				\
	db/migrate/20081126000659_create_connections.rb				\
	db/migrate/20081126001355_add_default_config_connection.rb		\
	db/migrate/20081202083637_add_connection_spec_to_milters.rb		\
	db/migrate/20081203131215_create_configurations.rb			\
	db/migrate/20081209042157_create_applicable_conditions.rb		\
	db/migrate/20081209074801_create_restrictions.rb			\
	db/migrate/20081209082702_remove_target_from_milters.rb			\
	db/migrate/20081212075410_add_enabled_to_milters.rb			\
	db/migrate/20081212080532_add_description_to_milters.rb			\
	db/migrate/20081214112549_decompose_spec.rb				\
	db/migrate/20081216125103_add_timeout_to_milters.rb			\
	db/migrate/20081216130836_add_user_name_to_milters.rb			\
	db/migrate/20090107013320_add_command_options_to_milters.rb		\
	db/migrate/20090116065917_create_users.rb				\
	db/migrate/20090512123747_add_fallback_status_to_milters.rb		\
	db/migrate/20090826132057_add_evaluation_mode_to_milters.rb		\
	doc/README_FOR_APP							\
	lib/authenticated_system.rb						\
	lib/authenticated_test_helper.rb					\
	lib/milter/manager.rb							\
	lib/milter/manager/connection_spec.rb					\
	lib/milter/manager/controller_client.rb					\
	lib/tasks/testing.rake							\
	public/404.html								\
	public/422.html								\
	public/500.html								\
	public/favicon.ico							\
	public/images/logo.png							\
	public/images/logo.svg							\
	public/images/menu-background.png					\
	public/images/menu-background.svg					\
	public/images/rails.png							\
	public/javascripts/application.js					\
	public/javascripts/controls.js						\
	public/javascripts/dragdrop.js						\
	public/javascripts/effects.js						\
	public/javascripts/prototype.js						\
	public/robots.txt							\
	public/stylesheets/base.css						\
	public/stylesheets/config.css						\
	test/fixtures/applicable_conditions.yml					\
	test/fixtures/configurations.yml					\
	test/fixtures/connections.yml						\
	test/fixtures/milters.yml						\
	test/fixtures/restrictions.yml						\
	test/fixtures/users.yml							\
	test/functional/config/applicable_conditions_controller_test.rb		\
	test/functional/config/connections_controller_test.rb			\
	test/functional/config/milters_controller_test.rb			\
	test/functional/config_controller_test.rb				\
	test/functional/control_controller_test.rb				\
	test/functional/sessions_controller_test.rb				\
	test/functional/users_controller_test.rb				\
	test/functional/welcome_controller_test.rb				\
	test/integration/connection_actions_test.rb				\
	test/integration/milter_actions_test.rb					\
	test/performance/browsing_test.rb					\
	test/test_helper.rb							\
	test/unit/config/applicable_condition_test.rb				\
	test/unit/config/connection_test.rb					\
	test/unit/config/milter_test.rb						\
	test/unit/config/restriction_test.rb					\
	test/unit/configuration_test.rb						\
	test/unit/connection_spec_test.rb					\
	test/unit/controller_client_test.rb					\
	test/unit/user_test.rb							\
	vendor/plugins/restful-auth/.gitignore					\
	vendor/plugins/restful-auth/CHANGELOG					\
	vendor/plugins/restful-auth/README.textile				\
	vendor/plugins/restful-auth/Rakefile					\
	vendor/plugins/restful-auth/TODO					\
	vendor/plugins/restful-auth/init.rb					\
	vendor/plugins/restful-auth/install.rb					\
	vendor/plugins/restful-auth/lib/authentication.rb			\
	vendor/plugins/restful-auth/lib/authentication/by_cookie_token.rb	\
	vendor/plugins/restful-auth/lib/authentication/by_password.rb		\
	vendor/plugins/restful-auth/lib/authorization.rb			\
	vendor/plugins/restful-auth/lib/authorization/aasm_roles.rb		\
	vendor/plugins/restful-auth/lib/authorization/stateful_roles.rb		\
	vendor/plugins/restful-auth/lib/tasks/auth.rake				\
	vendor/plugins/restful-auth/lib/trustification.rb			\
	vendor/plugins/restful-auth/lib/trustification/email_validation.rb	\
	vendor/plugins/restful-auth/notes/AccessControl.txt			\
	vendor/plugins/restful-auth/notes/Authentication.txt			\
	vendor/plugins/restful-auth/notes/Authorization.txt			\
	vendor/plugins/restful-auth/notes/RailsPlugins.txt			\
	vendor/plugins/restful-auth/notes/SecurityFramework.graffle		\
	vendor/plugins/restful-auth/notes/SecurityFramework.png			\
	vendor/plugins/restful-auth/notes/SecurityPatterns.txt			\
	vendor/plugins/restful-auth/notes/Tradeoffs.txt				\
	vendor/plugins/restful-auth/notes/Trustification.txt			\
	vendor/plugins/restful-auth/rails/init.rb				\
	vendor/plugins/restful-auth/restful-authentication.gemspec
