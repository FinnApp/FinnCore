## WIP

[![GitHub license](https://img.shields.io/github/license/Helkaris/FinnCore.svg)](https://github.com/Helkaris/FinnCore/blob/master/LICENSE)
 [![GitHub release](https://img.shields.io/github/release/Helkaris/FinnCore.svg)](https://GitHub.com/Helkaris/FinnCore/releases/) ![CI](https://github.com/Helkaris/FinnCore/workflows/CI/badge.svg?branch=master) [![codecov](https://codecov.io/gh/Helkaris/FinnCore/branch/master/graph/badge.svg)](https://codecov.io/gh/Helkaris/FinnCore)

### 0.1-alpha API
- Account
  - [x] Has ID
  - [x] Set/Update name
  - [x] Add/Remove/Get/Count wallets
  - [x] Add/Remove/Get/Count categories
  - [x] Overall balance
- Category
  - [x] Has ID
  - [x] Set/Update name
  - [x] Add/Remove/Get/Count subcategories
- Wallet
  - [x] Has ID
  - [x] Has initial balance
  - [x] Has balance from transactions
  - [x] Set/Update name
  - [x] Add/Remove/Get/Count transactions
- Transaction
  - [x] Has ID
  - [x] Set/Update wallet
  - [x] Set/Update category
  - [x] Set/Update date
  - [x] Set/Update description
  - [x] Set/Update amount
  - [x] Set/Update type (income/expense)

### Plans for 0.2-alpha API
- [ ] Store/Load services to preserve added entities
- Account
  - [ ] Add/Remove/Get/Count currencies
- Wallet
  - [ ] Set/Update currency
- Transaction
  - [ ] New transfer type
- Currency
  - [ ] Set/Update name
  - [ ] Rates with other currencies

### Plans for 0.3-alpha API
- Notification mechanism to track entities
- Transaction fee

### Plans for 0.4-alpha API
- Debts

### Plans for 0.5-alpha API
- Trips

### Plans for 0.6-alpha API
- Budgets

### Plans for 0.7-alpha API
- Basic stats

### Plans for 0.8-alpha API
- Basic stats

### Plans for 0.9-alpha API
- Filter transactions

### Plans for 0.10-alpha API
- Shopping list

### Plans for 0.11-alpha API
- Planned transactions

### Plans for 0.12-alpha API
- Subscriptions list

### Key ideas
- "Pay for me in both sides" - when someone or you pay goods for 2 more people in the shop the receipt can be splitted between others and countered as a debt. Basically, it means that single transaction splitted in subtransaction (your part and debts).
- Debts should be assigned to specific person. We should track debt history for debtors as well.
- If your friend or someone else is using this app debts are synchronized in all accounts
- Attach receipt photo, crop it, do some post-processing to be able to recognize all lines
- Transaction multi-select to change category/date for all of them
- Transaction with subtransactions
- Regular/planned/template transactions + notifications about planned/regular transactions
- Data import/export
- Calculator while entering transaction amount
- Bank sync (check manual transaction with bank transactions) with plugin system to extend banks
- Parse notifications
- Create categories that can be used only 1 type (income or expense)
- Business account for companies
- Project mode - your track spending/stats for specific project
- Scan a physical receipt to make a new record of expenses or incomes. Taking the description and value.
- "Close" an account so that the transactions for that account are retained in stats. Also, you can't make new transfers and transactions to this account.
- Rollover (savings in the previous month goes for the next) in budgets
- Money to goals should be transeferred as it was wallet
- Budget forecasting
- Calendar view for planned payments
- Invoice control: You could have the option to add to both expiration date and closing date, so the application would automatically close that invoice, throwing the next records to the next invoice. That way it would be simple to make a check of which purchases came in the invoice that month, for example. This information could be checked in the statistics.
Still on invoices, we could, with item 1 implemented, have the option to pay the invoice with the balance of some account, as happens today with the "debits", through a button "pay / anticipate invoice"
- Credit card management
- Networth monitoring.
- Budget should be different for different month / yea
- Budget should tell the average spend for the budget in last 6 months/1 year
- Financial Independence Retire Early (FIRE) target number is the year (or how many years) you reach financial independence and there is no need to work anymore. Normally is the year when total balance reaches 25 times yearly spending.
