#include "Transaction.hpp"

#include <boost/date_time/local_time/local_time.hpp>

Transaction::ZeroAmountError::ZeroAmountError() : std::runtime_error{"Transaction amount should not be 0.0"} {}

Transaction::InvalidWallet::InvalidWallet() : std::runtime_error{"Transaction created with invalid wallet"} {}

Transaction::InvalidCategory::InvalidCategory() : std::runtime_error{"Transaction created with invalid category"} {}

Transaction::InvalidDateTime::InvalidDateTime() : std::runtime_error{"Transaction created with invalid date/time"} {}

Transaction::Transaction(Id id,
                         double amount,
                         std::weak_ptr<Wallet> wallet,
                         std::weak_ptr<Category> category,
                         const DateTime& dateTime) :
    UniqueEntity{id}
{
    updateAmount(amount);
    updateWallet(wallet);
    updateCategory(category);
    updateDateTime(dateTime);
}

Transaction::Transaction(Id id, double amount, std::weak_ptr<Wallet> wallet, std::weak_ptr<Category> category) :
    Transaction{id, amount, wallet, category, boost::posix_time::second_clock::local_time()}
{
}

double Transaction::amount() const
{
    return amount_;
}

void Transaction::updateAmount(double amount)
{
    if (amount_ == 0.0) throw ZeroAmountError{};

    amount_ = amount;
}

std::weak_ptr<Wallet> Transaction::wallet() const
{
    assert(!wallet_.expired());

    return wallet_;
}

void Transaction::updateWallet(const std::weak_ptr<Wallet>& wallet)
{
    if (wallet.expired()) throw InvalidWallet{};

    wallet_ = wallet;
}

std::weak_ptr<Category> Transaction::category() const
{
    return category_;
}

void Transaction::updateCategory(const std::weak_ptr<Category>& category)
{
    if (category.expired()) throw InvalidCategory{};

    category_ = category;
}

const DateTime& Transaction::dateTime() const
{
    return dateTime_;
}

void Transaction::updateDateTime(const DateTime& dateTime)
{
    if (dateTime.is_special()) throw InvalidDateTime{};

    dateTime_ = dateTime;
}

Date Transaction::date() const
{
    return dateTime_.date();
}

Time Transaction::time() const
{
    return dateTime_.time_of_day();
}

Transaction::Type Transaction::type() const
{
    return amount_ < 0.0 ? Type::Expense : Type::Income;
}

const std::string& Transaction::description() const
{
    return description_;
}

void Transaction::updateDescription(const std::string& description)
{
    description_ = description;
}
