general_ledger
==============

What is it?
-----------

**general_ledger** will be a fully-featured, multi-user, multi-entity,
open-source client-server general ledger system. Development is still at an
early stage.

Planned near-term features include:

* Multi-user environment with finely-grained access rights
* Separation of create and post rights
* Multiple entities and consolidation
* Full period-end and year-end close functionality
* Client applications

Planned long-term features include:

* Support for all major database platforms
* Separate integrated modules, e.g. cash, fixed assets, accounts payable and
receivable

**general_ledger** is a working title.

Who maintains it?
-----------------
**general_ledger** is written and maintained by Paul Griffiths.

The latest version
------------------
Details of the latest version can be found on the GitHub project page at
<https://github.com/paulgriffiths/general_ledger>.

Documentation
-------------
Up-to-date documentation can be found at
<https://github.com/paulgriffiths/general_ledger/wiki>.

Installation
------------
**general_ledger** is written in C++. Type `make` to build. Development is still
at an early stage, but the instructions below may be followed to create a
database and work with sample data to get started working on the project.

To run general ledger, a database and appropriate users must be separately
set up. Currently, only MySQL databases are supported. It is recommended to
create an admin user with all rights, and a regular user with SELECT and
INSERT rights.

Update the file `conf_files/gl_db_conf.conf` with the hostname and database
name, and the name of the admin user. Update the file
`conf_files/gl_reports_conf.conf` with the hostname and database name, and the
name of the regular user.

`gl_db --init` may be run to delete an existing general ledger database
structure (if one exists), create a new database structure, and load it with
some provided sample data. `gl_db --delete`, `gl_db --create`, and
`gl_db --loadsample` may be used to run these operations individually.

On successful creation and loading of sample date, `gl_report` may be used to
run reports on the sample data. Some sample commands are:

* `gl_report --listusers` - list users
* `gl_reports --listentities` - list the corporate entities in the ledger
* `gl_report --currenttb --entity=1` - show the current trial balance for
corporate entity number 1
* `gl_reports --entries` - show all journal entries
* `gl_report --entries=1` - show journal entry number 1.

Both `gl_db` and `gl_report` respond to the `--help` option to
show a full list of supported options.

Licensing
---------
Please see the file called LICENSE.

Contacts
--------
* If you have a concrete bug report for **general_ledger** please go to the
GitHub issue tracker at
<https://github.com/paulgriffiths/general_ledger/issues>.

