#ifndef CONNECTIONSDIALOG_H
#define CONNECTIONSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHash>
#include "settings/ConnectionRecord.h"
#include "settings/SettingsManager.h"
#include <boost/scoped_ptr.hpp>
#include "Core.h"

using namespace boost;

namespace Robomongo
{
    /**
     * @brief Forward declaration
     */
    class ConnectionListWidgetItem;

    /**
     * @brief Dialog allows select/edit/add/delete connections
     */
    class ConnectionsDialog : public QDialog
    {
        Q_OBJECT

    private:

        /**
         * @brief Main list widget
         */
        QListWidget *_listWidget;

        /**
         * @brief Settings manager
         */
        SettingsManager *_settingsManager;

        /**
         * @brief Hash that helps to connect ConnectionRecord with ConnectionListWidgetItem*
         */
        QHash<ConnectionRecordShared, ConnectionListWidgetItem *> _hash;

    public:

        /**
         * @brief Creates dialog
         */
        ConnectionsDialog(SettingsManager *manager);

        /**
         * @brief This function is called when user clicks on "Connect" button.
         */
        virtual void accept();

    private slots:

        /**
         * @brief Add connection to the list widget
         */
        void add(const ConnectionRecordShared &connection);

        /**
         * @brief Update specified connection (if it exists for this dialog)
         */
        void update(const ConnectionRecordShared &connection);

        /**
         * @brief Remove specified connection (if it exists for this dialog)
         */
        void remove(const ConnectionRecordShared &connection);

        /**
         * @brief Initiate 'add' action, usually when user clicked on Add button
         */
        void add();

        /**
         * @brief Initiate 'edit' action, usually when user clicked on Edit button
         */
        void edit();

        /**
         * @brief Initiate 'remove' action, usually when user clicked on Remove button
         */
        void remove();
    };

    /**
     * @brief Simple ListWidgetItem that has several convenience methods.
     */
    class ConnectionListWidgetItem : public QListWidgetItem
    {
    public:

        /**
         * @brief Returns attached ConnectionRecord.
         */
        ConnectionRecordShared connection()
        {
            QVariant var = data(Qt::UserRole);
            return var.value<ConnectionRecordShared>();
        }

        /**
         * @brief Attach ConnectionRecord to this item
         */
        void setConnection(ConnectionRecordShared connection)
        {
            setText(connection->connectionName());
            setData(Qt::UserRole, QVariant::fromValue<ConnectionRecordShared>(connection));
        }
    };
}


#endif // CONNECTIONSDIALOG_H