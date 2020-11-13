#ifndef FIFO_HPP_
#define FIFO_HPP_


template<typename tType, unsigned uSize>
class FIFO
{
    private:
        struct item
        {
            tType data;
            bool used;
            item *pNext;
        };

        item buffer[uSize] = {{0},0};
        
        /* Points to item to be read. */
        item *pNextToBeRead;
        item *pLastInserted;

    public:
        FIFO():
            pNextToBeRead(nullptr),
            pLastInserted(nullptr)
            {}

        void push_back(tType atItem)
        {
            item *currItem = buffer;
            item *lastItem = buffer + uSize;

            /* Linear search for next vacant spot */
            while(currItem < lastItem)
            {
                if(!currItem->used)
                {
                    currItem->data = atItem;
                    currItem->used = true;

                    if(pLastInserted != nullptr)
                        (pLastInserted->pNext = currItem);
                    if(pNextToBeRead == nullptr)
                        pNextToBeRead = currItem;

                    pLastInserted = currItem;
                    break;
                }

                currItem++;
            }
        }

        tType *read(void)
        {
            if(pNextToBeRead == nullptr)
            {
                return nullptr;
            }

            tType *tRetVal = &pNextToBeRead->data;
            pNextToBeRead->used = false;
            pNextToBeRead = pNextToBeRead->pNext;

            if(pNextToBeRead == pLastInserted)
            {
                pNextToBeRead->pNext = nullptr;
            }

            return tRetVal;
        }

        void purge(void)
        {
            for(unsigned i = 0; i < uSize; i++)
            {
                buffer[i].used = false;
            }
        }
};

#endif /* FIFO_HPP_ */